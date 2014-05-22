#include "dragonfly.h"

Browser *browsers = NULL;
char *cookiefile;
char *stylefile;
char *download_dir;

/*
 * Destroy all browser instances
 */
static void
cleanup (void)
{
	while(browsers)
		destroy_browser (browsers);
	g_free (cookiefile);
	g_free (stylefile);
	g_free (download_dir);
}

static void
setup (void)
{
	SoupSession *s;
	
	/* dirs and files */
	cookiefile = buildpath (COOKIE_FILE);
	stylefile = buildpath (STYLE_FILE);
	download_dir = buildpath (DOWNLOAD_DIR);
	
	/* request handler */
	s = webkit_get_default_session ();
	
	/* cookie jar */
	soup_session_add_feature (s, SOUP_SESSION_FEATURE (cookiejar_new (cookiefile, FALSE)));
	
	/* ssl */
	g_object_set (G_OBJECT (s), "ssl-ca-file", CA_FILE, NULL);
	g_object_set (G_OBJECT (s), "ssl-strict", STRICT_SSL, NULL);
}

int
main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	
	setup ();
		
	if (argc > 1)
		if (argv[1][1] == 'v') {
			printf ("Dragonfly-"VERSION", 2014 David Luco\n");
			return 0;
		}
	
	Browser *b = browser_new ();
	gtk_window_set_title (GTK_WINDOW (b->window), "Dragonfly");
	
	gchar* uri = (gchar*) (argc > 1 ? argv[1] : HOME_PAGE);
	webkit_web_view_load_uri (b->webview, uri);
	
	gtk_main ();
	cleanup ();
	
	return 0;
}
