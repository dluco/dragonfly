#include "dragonfly.h"

#include <getopt.h>

Conf *main_conf = NULL;
Browser *browsers = NULL;
SearchEngine *engine_list = NULL;
char *cookiefile;
char *stylefile;
char *download_dir;
char *enginefile;

static void
init(void)
{
	SoupSession *s;
	
	/* dirs and files */
	cookiefile = buildpath(COOKIE_FILE);
	stylefile = buildpath(STYLE_FILE);
	download_dir = buildpath(DOWNLOAD_DIR);
	
	/* request handler */
	s = webkit_get_default_session();
	
	/* cookie jar */
	soup_session_add_feature(s, SOUP_SESSION_FEATURE(cookiejar_new(cookiefile, FALSE)));
	
	/* ssl */
	g_object_set(G_OBJECT(s), "ssl-ca-file", CA_FILE, NULL);
	g_object_set(G_OBJECT(s), "ssl-strict", STRICT_SSL, NULL);
	
	/* search engines */
	load_engines();
	
	/* conf for all browser instances */
	main_conf = conf_new();
	conf_init(main_conf);
	conf_load_from_file(main_conf);
}

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
	g_free (enginefile);
	
	conf_save_to_file(main_conf);
}

static void
parse_args (int argc, char **argv)
{
	int option_index = 0;
	int index;
	
	struct option long_options[] = {
		{"help", no_argument, 0, 'h'},
		{"useragent", required_argument, 0, 'u'},
		{"version", no_argument, 0, 'v'},
		{0, 0, 0, 0}
	};
	
	while ((index = getopt_long (argc, argv, "hu:v", long_options, &option_index)) != -1) {
		switch (index) {
			case 'h':
				printf ("help!\n");
				exit (0);
			case 'u':
				if (optarg)
					printf ("%s\n", optarg);
				break;
			case 'v':
				printf ("%s\n", "dragonfly-"VERSION);
				exit (0);
			default:
				printf ("%s\n", "chicken");
				break;
		}
	}
}

int
main (int argc, char *argv[])
{
	Browser *b;
	
	gtk_init(&argc, &argv);
//	parse_args(argc, argv);
	
	g_set_application_name("Dragonfly");
	
	init();
	
	b = browser_new(main_conf);
	gtk_window_set_title(GTK_WINDOW(b->window), "Dragonfly");
	
	gchar* uri = (gchar*) (argc > 1 ? argv[1] : main_conf->homepage);
	webkit_web_view_load_uri(b->webview, uri);
	
	gtk_main();
	cleanup();
	
	return 0;
}
