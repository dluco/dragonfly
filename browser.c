#include "dragonfly.h"

Browser*
create_browser ()
{
	Browser *b;
	
	if (!(b = malloc (sizeof (Browser))))
	{
		fprintf (stderr, "Error: Failed to allocate memory\n");
	}
	
	b->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_wmclass (GTK_WINDOW (b->window), "dragonfly", "Dragonfly");
	gtk_window_set_role (GTK_WINDOW (b->window), "Dragonfly");
	
	gtk_window_set_default_size (GTK_WINDOW (b->window), 800, 600);
	
	g_signal_connect (G_OBJECT (b->window),
		"delete-event",
		G_CALLBACK (destroy_window), b);
					
	b->next = browsers;
	
	gtk_widget_show (b->window);
	
	return b;
}
