#include "dragonfly.h"

static void
destroy_client (Browser *b)
{
	Browser *p;
	
	/*
	 * webkit things
	*/
	
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

static void
destroy_window (GtkWidget* w, Browser *b)
{
	destroy_client (b);
}
