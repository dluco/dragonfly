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
on_print (GtkWidget *w, Browser *b)
{
	webkit_web_frame_print (webkit_web_view_get_main_frame (b->webview));
}
