#include "dragonfly.h"

SearchEngine *
browser_get_default_search_engine (Browser *b)
{
	SearchEngine *engine;
	
	if (!(engine = malloc (sizeof (SearchEngine)))) {
		fprintf (stderr, "Error: Failed to allocate memory\n");
	}
	
	engine->name = "Duck Duck Go";
	engine->url = "https://duckduckgo.com/?q=";
	
	return engine;
}

void
browser_set_default_search_engine (Browser *b, SearchEngine *engine)
{
	b->engine = engine;
}

void
browser_set_settings (Browser *b)
{
	WebKitWebSettings *settings;
	
	settings = webkit_web_view_get_settings (b->webview);
	
	/* Apply default settings from config.h */
	g_object_set (G_OBJECT (settings), "user-agent", useragent, NULL);
	g_object_set (G_OBJECT (settings), "auto-load-images", LOAD_IMAGES, NULL);
	g_object_set (G_OBJECT (settings), "enable-plugins", ENABLE_PLUGINS, NULL);
	g_object_set (G_OBJECT (settings), "enable-scripts", ENABLE_SCRIPTS, NULL);
	g_object_set (G_OBJECT (settings), "enable-spatial-navigation", ENABLE_SPATIAL_BROWSING, NULL);
	g_object_set (G_OBJECT (settings), "enable-spell-checking", ENALBE_SPELL_CHECKING, NULL);
	g_object_set (G_OBJECT (settings), "enable-file-access-from-file-uris", ENABLE_FILE_ACCESS, NULL);
	g_object_set (G_OBJECT (settings), "enable-developer-extras", ENABLE_INSPECTOR, NULL);
	
	webkit_web_view_set_transparent (b->webview, HIDE_BACKGROUND);
	webkit_web_view_set_full_content_zoom (b->webview, FULL_CONTENT_ZOOM);
	
	/* Initialize fullscreen, zoomed, and isinspecting */
	b->fullscreen = FALSE;
	b->isinspecting = FALSE;
	b->zoomed = FALSE;
	
	if(ENABLE_INSPECTOR) {
		b->inspector = WEBKIT_WEB_INSPECTOR (webkit_web_view_get_inspector (b->webview));
		g_signal_connect (G_OBJECT (b->inspector), "inspect-web-view",
			G_CALLBACK (inspector_new), b);
		g_signal_connect (G_OBJECT (b->inspector), "show-window",
			G_CALLBACK (inspector_show), b);
		g_signal_connect(G_OBJECT (b->inspector), "close-window",
			G_CALLBACK (inspector_close), b);
		g_signal_connect(G_OBJECT (b->inspector), "finished",
			G_CALLBACK (inspector_finished), b);
		b->isinspecting = FALSE;
	}
}

/*
 * Create a new Browser instance, containing a scrolled webview and
 * statusbar. A pane is used to hold the webview for when the
 * webinspector is called, which occupies the lower pane.
 */
Browser *
browser_new ()
{
	Browser *b;
	
	if (!(b = malloc (sizeof (Browser)))) {
		fprintf (stderr, "Error: Failed to allocate memory\n");
	}
	
	b->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_wmclass (GTK_WINDOW (b->window), "dragonfly", "Dragonfly");
	gtk_window_set_role (GTK_WINDOW (b->window), "Dragonfly");
	gtk_window_set_icon_name (GTK_WINDOW (b->window), "web-browser");
	
	gtk_window_set_default_size (GTK_WINDOW (b->window), 800, 600);
	
	g_signal_connect (G_OBJECT (b->window),
		"destroy",
		G_CALLBACK (destroy_window), b);
	
	/* Pane */
	b->pane = gtk_vpaned_new ();
	
	/* VBox */
	b->vbox = gtk_vbox_new (FALSE, 0);
	
	/* Menubar */
	b->menubar = create_menubar (b);
	
	/* Toolbar */
	b->toolbar = create_toolbar (b);
	
	/* Scrolled Window */
	b->scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (b->scrolled_window),
		GTK_POLICY_NEVER, GTK_POLICY_NEVER);
	
	/* Webview */
	b->webview = WEBKIT_WEB_VIEW (webkit_web_view_new ());
	g_signal_connect (G_OBJECT (b->webview),
		"create-web-view",
		G_CALLBACK (create_window), b);
	g_signal_connect (G_OBJECT (b->webview),
		"hovering-over-link",
		G_CALLBACK (link_hover), b);
	g_signal_connect (G_OBJECT (b->webview),
		"mime-type-policy-decision-requested",
		G_CALLBACK (decide_download), b);
	g_signal_connect (G_OBJECT (b->webview),
		"download-requested",
		G_CALLBACK (init_download), b);
	g_signal_connect (G_OBJECT (b->webview),
		"notify::load-status",
		G_CALLBACK (load_status_change), b);
	g_signal_connect (G_OBJECT (b->webview),
		"notify::progress",
		G_CALLBACK (progress_change), b);
	g_signal_connect(G_OBJECT(b->webview),
		"title-changed",
		G_CALLBACK(title_change), b);
	
	browser_set_settings (b);
	
	/* Statusbar */
	b->status_bar = GTK_STATUSBAR (gtk_statusbar_new ());
	b->status_context_id = gtk_statusbar_get_context_id (b->status_bar, "Link Hover");
	
	/* Arrange containers */
	gtk_container_add (GTK_CONTAINER (b->scrolled_window), GTK_WIDGET (b->webview));
	gtk_paned_pack1 (GTK_PANED (b->pane), b->scrolled_window, TRUE, TRUE);
	gtk_box_pack_start (GTK_BOX (b->vbox), b->menubar, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (b->vbox), b->toolbar, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (b->vbox), b->pane, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (b->vbox), GTK_WIDGET (b->status_bar), FALSE, FALSE, 0);
	gtk_container_add (GTK_CONTAINER (b->window), b->vbox);
	
	/* Setup */
	gtk_box_set_child_packing (GTK_BOX (b->vbox), b->scrolled_window, TRUE,
		TRUE, 0, GTK_PACK_START);
	gtk_widget_grab_focus (GTK_WIDGET (b->webview));
	gtk_widget_show (GTK_WIDGET (b->webview));
	gtk_widget_show (b->scrolled_window);
	gtk_widget_show (b->menubar);
	gtk_widget_show (b->toolbar);
	gtk_widget_show (b->pane);
	gtk_widget_show (GTK_WIDGET (b->status_bar));
	gtk_widget_show (b->vbox);
	gtk_widget_show (b->window);
	
	b->title = NULL;
	b->next = browsers;
	browsers = b;
	
	/* Search Engine */
	b->engine = browser_get_default_search_engine (b);
	
	gtk_widget_show (b->window);
	
	return b;
}
