#include "dragonfly.h"

/*
 * Activation of the url-bar - open web page in web-view
 */
void
activate_uri_entry (GtkWidget *entry, Browser *b)
{
	const gchar* uri;
	const gchar* temp = gtk_entry_get_text (GTK_ENTRY (entry));
	
	/* Append appropriate prefix */
	if (temp[0] == '/')
		uri = g_strdup_printf ("file://%s", temp);
	else
		uri = g_strrstr (temp, "://") ? g_strdup (temp) : g_strdup_printf ("https://%s", temp);
	
	webkit_web_view_load_uri (b->webview, uri);
}

/*
 * Callback for pop-up context menu
 * 
 * Determine if right mouse button was clicked on the menubar or toolbar
 */
gboolean
context_menu_popup (GtkWidget *widget, GdkEventButton *event, Browser *b)
{
	/* single click with the right mouse button? */
	if (event->type == GDK_BUTTON_PRESS && event->button == 3) {
		view_context_menu_popup (widget, event, b);
		return TRUE;
	}
	return FALSE;
}

/*
 * Create a new browser instance with the provided webview.
 */
WebKitWebView *
create_window (WebKitWebView  *v, WebKitWebFrame *f, Browser *b)
{
	Browser *n = create_browser ();
	return n->webview;
}

/*
 * Destroy all widgets inside a browser instance, and remove from
 * browser linked list.
 */
void
destroy_browser (Browser *b)
{
	Browser *p;
	
	webkit_web_view_stop_loading (b->webview);
	gtk_widget_destroy (GTK_WIDGET (b->webview));
	gtk_widget_destroy (b->scrolled_window);
	gtk_widget_destroy (b->vbox);
	gtk_widget_destroy (b->window);
	
	for (p = browsers; p && p->next != b; p = p->next);
	
	if (p) {
		p->next = b->next;
	} else {
		browsers = b->next;
	}
	
	free (b);

	if (browsers == NULL)
		gtk_main_quit ();
}

/*
 * Destroy the browser instance provided.
 */
void
destroy_window (GtkWidget* widget, Browser *b)
{
	destroy_browser (b);
}


void
fullscreen (GtkWidget *w, Browser *b)
{
	//Browser *b = data;
	
	if (b->fullscreen) {
		gtk_window_unfullscreen (GTK_WINDOW (b->window));
	} else {
		gtk_window_fullscreen (GTK_WINDOW (b->window));
	}
	b->fullscreen = !b->fullscreen;
}

void
go_back (GtkWidget* w, Browser *b)
{
	webkit_web_view_go_back (b->webview);
}

void
go_forward (GtkWidget* w, Browser *b)
{
	webkit_web_view_go_forward (b->webview);
}

void
go_home (GtkWidget *w, Browser *b)
{
	webkit_web_view_load_uri (b->webview, HOME_PAGE);
}

/*
 * Hide or show a widget based on its current visibility
 */
void
toggle_widget (GtkWidget *widget, gpointer data)
{
	/*data = GTK_WIDGET (data) */
	
	if (gtk_widget_get_visible (data) == TRUE) {
		gtk_widget_hide (data);
		return;
	}
	gtk_widget_show (data);
	return;
}

WebKitWebView *
inspector_new (WebKitWebInspector *i, WebKitWebView *v, Browser *b)
{
	return WEBKIT_WEB_VIEW (webkit_web_view_new ());
}

gboolean
inspector_show (WebKitWebInspector *i, Browser *b)
{
	WebKitWebView *w;

	if (b->isinspecting)
		return FALSE;

	w = webkit_web_inspector_get_web_view (i);
	gtk_paned_pack2 (GTK_PANED (b->pane), GTK_WIDGET (w), TRUE, TRUE);
	gtk_widget_show (GTK_WIDGET (w));
	b->isinspecting = TRUE;

	return TRUE;
}

gboolean
inspector_close (WebKitWebInspector *i, Browser *b)
{
	GtkWidget *w;

	if (!b->isinspecting)
		return FALSE;

	w = GTK_WIDGET (webkit_web_inspector_get_web_view (i));
	gtk_widget_hide (w);
	gtk_widget_destroy (w);
	b->isinspecting = FALSE;

	return true;
}

void
inspector_finished (WebKitWebInspector *i, Browser *b)
{
	g_free (b->inspector);
}

void
inspector_toggle (GtkWidget *w, Browser *b)
{
	if (b->isinspecting) {
		webkit_web_inspector_close (b->inspector);
		//gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (w), !b->isinspecting);
	} else {
		webkit_web_inspector_show (b->inspector);
		//gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (w), !b->isinspecting);
	}
}

/*
 * When hovering over a link, show in statusbar
 */
void
link_hover (WebKitWebView* page, const gchar* title, const gchar* link, Browser *b)
{
	/* underflow is allowed */
	gtk_statusbar_pop (b->status_bar, b->status_context_id);
	if (link)
		gtk_statusbar_push (b->status_bar, b->status_context_id, link);
}

void
load_status_change (WebKitWebView *view, GParamSpec *pspec, Browser *b)
{
	WebKitWebFrame* frame;
	const gchar* uri;
	
	switch (webkit_web_view_get_load_status (b->webview)) {
		case WEBKIT_LOAD_COMMITTED:
			/* Update uri in entry-bar */
			frame = webkit_web_view_get_main_frame (b->webview);
			uri = webkit_web_frame_get_uri (frame);
			if (uri)
				gtk_entry_set_text (GTK_ENTRY (b->uri_entry), uri);
			break;
		case WEBKIT_LOAD_FINISHED:
			b->progress = 100;
			break;
		default:
			break;
	}
	/* Update toolbar buttons */
	gtk_widget_set_sensitive (GTK_WIDGET (b->back_button), webkit_web_view_can_go_back (b->webview));
	gtk_widget_set_sensitive (GTK_WIDGET (b->forward_button), webkit_web_view_can_go_forward (b->webview));
}

/*
 * Edit/Cut - cut current selection
 */
void
on_edit_cut (GtkWidget* widget, Browser *b)
{	
	if (gtk_widget_has_focus (b->uri_entry))
		g_signal_emit_by_name (b->uri_entry, "cut-clipboard");
	else if (gtk_widget_has_focus (b->search_engine_entry))
		g_signal_emit_by_name (b->search_engine_entry, "cut-clipboard");
	else
		webkit_web_view_cut_clipboard (b->webview);
}

/*
 * Edit/Copy - copy current selection
 */
void
on_edit_copy (GtkWidget* widget, Browser *b)
{	
	if (gtk_widget_has_focus (b->uri_entry))
		g_signal_emit_by_name (b->uri_entry, "copy-clipboard");
	else if (gtk_widget_has_focus (b->search_engine_entry))
		g_signal_emit_by_name (b->search_engine_entry, "copy-clipboard");
	else
		webkit_web_view_copy_clipboard (b->webview);
}

/* 
 * Edit/Delete - delete current selection
 */
void
on_edit_delete (GtkWidget *widget, Browser *b)
{	
	if (gtk_widget_has_focus (b->uri_entry))
		g_signal_emit_by_name (b->uri_entry, "delete-from-cursor");
	else if (gtk_widget_has_focus (b->search_engine_entry))
		g_signal_emit_by_name (b->search_engine_entry, "delete-from-cursor");
	else
		webkit_web_view_delete_selection (b->webview);
}

/*
 * Edit/Paste - paste clipboard
 */
void
on_edit_paste (GtkWidget *widget, Browser *b)
{
	if (gtk_widget_has_focus (b->uri_entry))
		g_signal_emit_by_name (b->uri_entry, "paste-clipboard");
	else if (gtk_widget_has_focus (b->search_engine_entry))
		g_signal_emit_by_name (b->search_engine_entry, "paste-clipboard");
	else
		webkit_web_view_paste_clipboard (b->webview);
}

void
on_file_open (GtkWidget *w, Browser *b)
{
	GtkWidget* file_dialog;
	GtkFileFilter* filter;
	gchar *filename;
	
	/*Browser *b = data;*/
	
	file_dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW (b->window), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
	
	/* Add filters to dialog - all and html files */
	filter = gtk_file_filter_new ();
	gtk_file_filter_set_name (filter, "All files");
	gtk_file_filter_add_pattern (filter, "*");
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (file_dialog), filter);
	
	filter = gtk_file_filter_new ();
	gtk_file_filter_set_name (filter, "HTML files");
	gtk_file_filter_add_mime_type (filter, "text/html");
	gtk_file_filter_add_pattern (filter, "*.htm");
	gtk_file_filter_add_pattern (filter, "*.html");
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (file_dialog), filter);
	
	/* Run the dialog and check result. If a file was selected, open it in the web-view. */							
	if (gtk_dialog_run (GTK_DIALOG (file_dialog)) == GTK_RESPONSE_ACCEPT) {
		filename = g_strdup_printf("file://%s", gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (file_dialog)));
		webkit_web_view_load_uri (WEBKIT_WEB_VIEW (b->webview), filename);
		g_free (filename);
	}
	
	gtk_widget_destroy (file_dialog);
}

void
on_file_print (GtkWidget *w, Browser *b)
{
	/*Browser *b = data;*/
	webkit_web_frame_print (webkit_web_view_get_main_frame (b->webview));
}

void
on_file_quit (GtkWidget *w, Browser *b)
{	
	/*HACK: calling destroy_window (b) directly produces seg fault */
	g_signal_emit_by_name (b->window, "destroy");
}

void
progress_change (WebKitWebView *view, GParamSpec *pspec, Browser *b)
{
	b->progress = webkit_web_view_get_progress (b->webview) * 100;
	update_browser (b);
}

void
refresh (GtkWidget* w, Browser *b)
{
	webkit_web_view_reload (b->webview);
}

void
title_change (WebKitWebView *view, WebKitWebFrame *frame, const char *t, Browser *b)
{
	if (b->title)
		g_free (b->title);
	b->title = g_strdup (t);
	update_browser (b);
}

void
update_browser (Browser *b)
{
	GString *string;
	gchar *title;
	
	string = g_string_new (b->title);
	g_string_append (string, " - Dragonfly");
	
	if (b->progress != 100)
		g_string_append_printf (string, " (%d%%)", b->progress);
	
	title = g_string_free (string, FALSE);
	
	gtk_window_set_title (GTK_WINDOW (b->window), title);
	
	g_free (title);
}

/*
 * Display context menu for menubar and statusbar visibility
 */
void
view_context_menu_popup (GtkWidget *widget, GdkEventButton *event,  Browser *b)
{
	GtkWidget *menu;
	GtkWidget *hide_menu_bar_item;
	GtkWidget *hide_status_bar_item;
	
	menu = gtk_menu_new ();

	hide_menu_bar_item = gtk_check_menu_item_new_with_label ("Menu Bar");
	hide_status_bar_item = gtk_check_menu_item_new_with_label ("Status Bar");
	
	/* Set initial state of toggle to show if menubar is visible */
	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (hide_menu_bar_item), gtk_widget_get_visible (b->menubar));
	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (hide_status_bar_item), gtk_widget_get_visible (GTK_WIDGET (b->status_bar)));
	
	g_signal_connect (hide_menu_bar_item, "activate", G_CALLBACK (toggle_widget), b->menubar);
	g_signal_connect (hide_status_bar_item, "activate", G_CALLBACK (toggle_widget), b->status_bar);
	
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), hide_menu_bar_item);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), hide_status_bar_item);
	
	gtk_widget_show_all (menu);
	
	/* Trigger the popup menu to appear */
	gtk_menu_popup (GTK_MENU (menu), NULL, NULL, NULL, NULL, (event != NULL) ? event->button : 0, gdk_event_get_time ((GdkEvent*)event));
}

void
view_source (GtkWidget *w, Browser *b)
{
	gboolean state;

	state = webkit_web_view_get_view_source_mode (b->webview);
	webkit_web_view_set_view_source_mode (b->webview, !state);
	refresh (w, b);
}

/*
 * Zoom in web-view by 10%
 */
void
zoom_in (GtkWidget *widget, Browser *b)
{
	b->zoomed = TRUE;
	webkit_web_view_zoom_in (b->webview);
}

/*
 * Zoom out web-view by 10%
 */
void
zoom_out (GtkWidget *widget, Browser *b)
{
	b->zoomed = TRUE;
	webkit_web_view_zoom_out (b->webview);
}

/*
 * Reset zoom level to 100%
 */
void
zoom_reset (GtkWidget *widget, Browser *b)
{
	b->zoomed = FALSE;
	webkit_web_view_set_zoom_level (b->webview, 1.0);
}
