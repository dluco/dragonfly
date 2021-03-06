#include <stdio.h>
#include <stdlib.h>
#include "browser.h"
#include "searchengine.h"
#include "callback.h"
#include "download.h"
#include "menu.h"
#include "toolbar.h"

extern Config *main_conf;
extern Browser *browsers;

SearchEngine *browser_get_default_search_engine(Browser *b)
{	
	return b->engine;
}

void browser_set_default_search_engine(Browser *b, SearchEngine *engine)
{
	b->engine = engine;
	main_conf->engine = engine->name;
}

void browser_set_settings(Browser *b, Config *conf)
{
	WebKitWebSettings *settings;
	
	settings = webkit_web_view_get_settings(b->webview);
	
	/* Apply settings from conf */
	g_object_set(G_OBJECT(settings), "user-agent", conf->useragent, NULL);
	g_object_set(G_OBJECT(settings), "auto-load-images", conf->loadimages, NULL);
	g_object_set(G_OBJECT(settings), "enable-plugins", conf->enableplugins, NULL);
	g_object_set(G_OBJECT(settings), "enable-scripts", conf->enablescripts, NULL);
	g_object_set(G_OBJECT(settings), "enable-spatial-navigation", conf->enablespatialbrowsing, NULL);
	g_object_set(G_OBJECT(settings), "enable-spell-checking", conf->enablespellchecking, NULL);
	g_object_set(G_OBJECT(settings), "enable-file-access-from-file-uris", conf->enablefileaccess, NULL);
	g_object_set(G_OBJECT(settings), "enable-developer-extras", conf->enableinspector, NULL);
	
	webkit_web_view_set_transparent(b->webview, conf->hidebackground);
	webkit_web_view_set_full_content_zoom(b->webview, conf->fullcontentzoom);
	
	/* Initialize fullscreen, zoomed, and isinspecting */
	b->fullscreen = FALSE;
	b->isinspecting = FALSE;
	b->zoomed = FALSE;
	
	if (conf->enableinspector) {
		b->inspector = WEBKIT_WEB_INSPECTOR(webkit_web_view_get_inspector(b->webview));
		g_signal_connect(G_OBJECT(b->inspector), "inspect-web-view",
			G_CALLBACK(inspector_new), b);
		g_signal_connect(G_OBJECT(b->inspector), "show-window",
			G_CALLBACK(inspector_show), b);
		g_signal_connect(G_OBJECT(b->inspector), "close-window",
			G_CALLBACK(inspector_close), b);
		g_signal_connect(G_OBJECT(b->inspector), "finished",
			G_CALLBACK(inspector_finished), b);
		b->isinspecting = FALSE;
	}
	
	b->engine = search_engine_list_find(conf->engine);

	/* check if window should be maximized */
	if (conf->windowstate) {
		gtk_window_maximize(GTK_WINDOW(b->window));
	}
}

/*
 * Create a new Browser instance, containing a scrolled webview and
 * statusbar. A pane is used to hold the webview for when the
 * webinspector is called, which occupies the lower pane.
 */
Browser *browser_new(Config *conf)
{
	Browser *b;
	
	if (!(b = malloc(sizeof(Browser)))) {
		fprintf(stderr, "Error: Failed to allocate memory\n");
	}

	b->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_wmclass(GTK_WINDOW(b->window), "dragonfly", "Dragonfly");
	gtk_window_set_role(GTK_WINDOW(b->window), "Dragonfly");
	gtk_window_set_icon_name(GTK_WINDOW(b->window), "web-browser");
	
	gtk_window_set_default_size(GTK_WINDOW(b->window), 800, 600);
	
	g_signal_connect(G_OBJECT(b->window),
		"destroy",
		G_CALLBACK(destroy_window), b);
	g_signal_connect(G_OBJECT(b->window), "window-state-event", G_CALLBACK(window_state_event), b);
	
	/* Pane */
	b->pane = gtk_vpaned_new();
	
	/* VBox */
	b->vbox = gtk_vbox_new(FALSE, 0);
	
	/* Menubar */
	b->menubar = create_menubar(b);
	
	/* Toolbar */
	b->toolbar = create_toolbar(b);
	b->engine_menu = create_engine_menu(b);
	
	/* Scrolled Window */
	b->scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(b->scrolled_window),
		GTK_POLICY_NEVER, GTK_POLICY_NEVER);
	
	/* Webview */
	b->webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
	g_signal_connect(G_OBJECT(b->webview),
		"create-web-view",
		G_CALLBACK(create_window), b);
	g_signal_connect(G_OBJECT(b->webview),
		"hovering-over-link",
		G_CALLBACK(link_hover), b);
	g_signal_connect(G_OBJECT(b->webview),
		"mime-type-policy-decision-requested",
		G_CALLBACK(decide_download), b);
	g_signal_connect(G_OBJECT(b->webview),
		"download-requested",
		G_CALLBACK(init_download), b);
	g_signal_connect(G_OBJECT(b->webview),
		"notify::load-status",
		G_CALLBACK(load_status_change), b);
	g_signal_connect(G_OBJECT(b->webview),
		"notify::progress",
		G_CALLBACK(progress_change), b);
	g_signal_connect(G_OBJECT(b->webview),
		"title-changed",
		G_CALLBACK(title_change), b);
	
	/* Statusbar */
	b->status_bar = GTK_STATUSBAR(gtk_statusbar_new());
	b->status_context_id = gtk_statusbar_get_context_id(b->status_bar, "Link Hover");
	
	/* Arrange containers */
	gtk_container_add(GTK_CONTAINER(b->scrolled_window), GTK_WIDGET(b->webview));
	gtk_paned_pack1(GTK_PANED(b->pane), b->scrolled_window, TRUE, TRUE);
	gtk_box_pack_start(GTK_BOX(b->vbox), b->menubar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(b->vbox), b->toolbar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(b->vbox), b->pane, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(b->vbox), GTK_WIDGET(b->status_bar), FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(b->window), b->vbox);
	
	/* Setup */
	gtk_box_set_child_packing(GTK_BOX(b->vbox), b->scrolled_window, TRUE,
		TRUE, 0, GTK_PACK_START);
	gtk_widget_grab_focus(GTK_WIDGET(b->webview));
	gtk_widget_show(GTK_WIDGET(b->webview));
	gtk_widget_show(b->scrolled_window);
	gtk_widget_show(b->menubar);
	gtk_widget_show(b->toolbar);
	gtk_widget_show(b->pane);
	gtk_widget_show(GTK_WIDGET(b->status_bar));
	gtk_widget_show(b->vbox);
	gtk_widget_show(b->window);
	
	b->title = NULL;
	b->next = browsers;
	browsers = b;
	
	browser_set_settings(b, conf);
	
	gtk_widget_show(b->window);
	
	return b;
}
