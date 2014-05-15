#include "dragonfly.h"

WebKitWebView *
create_window (WebKitWebView  *v, WebKitWebFrame *f, Browser *b)
{
	Browser *n = create_browser ();
	return n->webview;
}

void
destroy_browser (Browser *b)
{
	Browser *p;
	
	/*
	 * webkit things
	*/
	
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

void
destroy_window (GtkWidget* widget, Browser *b)
{
	destroy_browser (b);
}

/*
 * Callback for hovering over a link - show in statusbar
 */
void
link_hover (WebKitWebView* page, const gchar* title, const gchar* link, Browser *b)
{
	/* underflow is allowed */
	gtk_statusbar_pop (b->status_bar, b->status_context_id);
	if (link)
		gtk_statusbar_push (b->status_bar, b->status_context_id, link);
}
