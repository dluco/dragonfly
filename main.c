#include "dragonfly.h"

Browser *browsers = NULL;

/*
 * Destroy all browser instances
 */
static void
cleanup (void)
{
	while(browsers)
		destroy_browser (browsers);
}

int
main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	
	Browser *b = create_browser ();
	gtk_window_set_title (GTK_WINDOW (b->window), "Dragonfly");
	
	gchar* uri = (gchar*) (argc > 1 ? argv[1] : HOME_PAGE);
	webkit_web_view_load_uri (b->webview, uri);
	
	gtk_main ();
	cleanup ();
	
	return EXIT_SUCCESS;
}
