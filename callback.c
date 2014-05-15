#include "dragonfly.h"

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
