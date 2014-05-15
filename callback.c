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
