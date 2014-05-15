#include "dragonfly.h"

Browser *browsers = NULL;

int
main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	
	Browser *b = create_browser ();
	gtk_window_set_title (GTK_WINDOW (b->window), "Dragonfly");
	
	gtk_main ();
	
	return 0;
}
