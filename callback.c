#include "dragonfly.h"

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
	
	if (p)
	{
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

WebKitWebView *
inspector_new (WebKitWebInspector *i, WebKitWebView *v, Browser *b) {
	return WEBKIT_WEB_VIEW (webkit_web_view_new ());
}

gboolean
inspector_show (WebKitWebInspector *i, Browser *b) {
	WebKitWebView *w;

	if (b->isinspecting)
		return false;

	w = webkit_web_inspector_get_web_view (i);
	gtk_paned_pack2 (GTK_PANED (b->pane), GTK_WIDGET (w), TRUE, TRUE);
	gtk_widget_show (GTK_WIDGET (w));
	b->isinspecting = TRUE;

	return TRUE;
}

gboolean
inspector_close (WebKitWebInspector *i, Browser *b) {
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
inspector_finished (WebKitWebInspector *i, Browser *b) {
	g_free (b->inspector);
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
on_file_open (GtkWidget *w, gpointer data)
{
	GtkWidget* file_dialog;
	GtkFileFilter* filter;
	gchar *filename;
	
	Browser *b = data;
	
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
	if (gtk_dialog_run (GTK_DIALOG (file_dialog)) == GTK_RESPONSE_ACCEPT)
	{
		filename = g_strdup_printf("file://%s", gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (file_dialog)));
		webkit_web_view_load_uri (WEBKIT_WEB_VIEW (b->webview), filename);
		g_free (filename);
	}
	
	gtk_widget_destroy (file_dialog);
}

void
on_file_print (GtkWidget *w, gpointer data)
{
	Browser *b = data;
	webkit_web_frame_print (webkit_web_view_get_main_frame (b->webview));
}

void
on_file_quit (GtkWidget *w, gpointer data)
{
	Browser *b = data;
	/* HACK: calling destroy_window (b) directly produces seg fault */
	g_signal_emit_by_name (b->window, "destroy");
}

void
on_fullscreen (GtkWidget *w, gpointer data)
{
	Browser *b = data;
	
	if (b->fullscreen)
	{
		gtk_window_unfullscreen (GTK_WINDOW (b->window));
	} else
	{
		gtk_window_fullscreen (GTK_WINDOW (b->window));
	}
	b->fullscreen = !b->fullscreen;
}

void
refresh (GtkWidget* w, Browser *b)
{
	webkit_web_view_reload (b->webview);
}
