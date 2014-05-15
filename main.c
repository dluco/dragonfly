#include "dragonfly.h"

int
main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	
	Browser *b = create_browser ();
	gtk_window_set_title (GTK_WINDOW (b->window), VERSION);
	
	if (browsers != NULL)
		printf ("aRG!\n");
	
	gtk_main ();
	
	return 0;
}
