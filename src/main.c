#include "dragonfly.h"

#include <getopt.h>

Browser *browsers = NULL;
SearchEngine *engine_list = NULL;
char *cookiefile;
char *stylefile;
char *download_dir;
char *enginefile;

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
}

/*
static void
load_config_file(Conf *conf)
{
	FILE *fp;
	gchar *path;
	gchar buf[BUFSIZE];
	*gchar **num; used for checking program version (line 1 in config file) *
	
	path = g_build_filename(g_get_user_config_dir(), PACKAGE, PACKAGE "rc", NULL);
	
	fp = fopen(path, "r");
	g_free (path);
	if (!fp)
		return;
	
	if (fgets (buf, sizeof(buf), fp)) {
		fgets(buf, sizeof(buf), fp);
		conf->useragent = g_strdup(buf);
		fgets(buf, sizeof(buf), fp);
		conf->homepage = g_strdup(buf);
		fgets(buf, sizeof(buf), fp);
		conf->downloaddir = g_strdup(buf);
		fgets(buf, sizeof(buf), fp);
		conf->enableplugins = atoi(buf);
		fgets(buf, sizeof(buf), fp);
		conf->enablescripts = atoi(buf);
		fgets(buf, sizeof(buf), fp);
		conf->enablefileaccess = atoi(buf);
		fgets(buf, sizeof(buf), fp);
		conf->strictssl = atoi(buf);
		fgets(buf, sizeof(buf), fp);
		conf->enableinspector = atoi(buf);
		fgets(buf, sizeof(buf), fp);
		conf->loadimages = atoi(buf);
		fgets(buf, sizeof(buf), fp);
		conf->enablespatialbrowsing = atoi(buf);
		fgets(buf, sizeof(buf), fp);
		conf->enablespellchecking = atoi(buf);
		fgets(buf, sizeof(buf), fp);
		conf->hidebackground = atoi(buf);
		fgets(buf, sizeof(buf), fp);
		conf->fullcontentzoom = atoi(buf);
	}
	fclose(fp);
}
*/

static void
create_config_file (gchar *pathname)
{
	GKeyFile *key_file;
	
	key_file = g_key_file_new ();
	
	g_key_file_set_string (key_file, "Default", "version", VERSION);
	g_key_file_set_string (key_file, "Default", "useragent", USER_AGENT);
	g_key_file_set_string (key_file, "Default", "homepage", HOME_PAGE);
	g_key_file_set_string (key_file, "Default", "download-dir", DOWNLOAD_DIR);
	g_key_file_set_boolean (key_file, "Default", "enableplugins", ENABLE_PLUGINS);
	g_key_file_set_boolean (key_file, "Default", "enablescripts", ENABLE_SCRIPTS);
	g_key_file_set_boolean (key_file, "Default", "enablefileaccess", ENABLE_FILE_ACCESS);
	g_key_file_set_boolean (key_file, "Default", "strictssl", STRICT_SSL);
	g_key_file_set_boolean (key_file, "Default", "enableinspector", ENABLE_INSPECTOR);
	g_key_file_set_boolean (key_file, "Default", "loadimages", LOAD_IMAGES);
	g_key_file_set_boolean (key_file, "Default", "enablespatialbrowsing", ENABLE_SPATIAL_BROWSING);
	g_key_file_set_boolean (key_file, "Default", "enablespellchecking", ENABLE_SPELL_CHECKING);
	g_key_file_set_boolean (key_file, "Default", "hidebackground", HIDE_BACKGROUND);
	g_key_file_set_boolean (key_file, "Default", "fullcontentzoom", FULL_CONTENT_ZOOM);
	
	g_key_file_save_to_file (key_file, pathname, NULL);
	
	g_key_file_free (key_file);
}

static void
load_config_file (Conf *conf)
{
	GKeyFile *key_file;
	gchar *path;
	
	path = g_build_filename(g_get_user_config_dir(), PACKAGE, PACKAGE "rc", NULL);
	/* check if file exists */
	if (!g_file_test (path, G_FILE_TEST_EXISTS)) {
		/* config file does not exist - create with defaults */
		create_config_file (path);
	}
	
	key_file = g_key_file_new ();
	g_key_file_load_from_file (key_file, path, G_KEY_FILE_KEEP_COMMENTS, NULL);
	g_free (path);
	
	conf->useragent = g_key_file_get_string (key_file, "Default", "useragent", NULL);
	conf->homepage = g_key_file_get_string (key_file, "Default", "homepage", NULL);
	conf->engine = g_key_file_get_string (key_file, "Default", "engine", NULL);
	conf->downloaddir = g_key_file_get_string (key_file, "Default", "download-dir", NULL);
	conf->enableplugins = g_key_file_get_boolean (key_file, "Default", "enableplugins", NULL);
	conf->enablescripts = g_key_file_get_boolean (key_file, "Default", "enablescripts", NULL);
	conf->enablefileaccess = g_key_file_get_boolean (key_file, "Default", "enablefileaccess", NULL);
	conf->strictssl = g_key_file_get_boolean (key_file, "Default", "strictssl", NULL);
	conf->enableinspector = g_key_file_get_boolean (key_file, "Default", "enableinspector", NULL);
	conf->loadimages = g_key_file_get_boolean (key_file, "Default", "loadimages", NULL);
	conf->enablespatialbrowsing = g_key_file_get_boolean (key_file, "Default", "enablespatialbrowsing", NULL);
	conf->enablespellchecking = g_key_file_get_boolean (key_file, "Default", "enablespellchecking", NULL);
	conf->hidebackground = g_key_file_get_boolean (key_file, "Default", "hidebackground", NULL);
	conf->fullcontentzoom = g_key_file_get_boolean (key_file, "Default", "fullcontentzoom", NULL);
	
	g_key_file_free (key_file);
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
				printf ("%s\n", PACKAGE"-"VERSION);
				exit (0);
			default:
				printf ("%s\n", "chicken");
				break;
		}
	}
}

/*
static void
save_config_file(Conf *conf)
{
	FILE *fp;
	gchar *path;
	
	path = g_build_filename(g_get_user_config_dir(), PACKAGE, NULL);
	if (!g_file_test(path, G_FILE_TEST_IS_DIR)) {
		g_mkdir_with_parents(path, 0700);
	}
	g_free(path);
	path = g_build_filename(g_get_user_config_dir(), PACKAGE, PACKAGE "rc", NULL);
	fp = fopen(path, "w");
	if (!fp) {
		fprintf(stderr, "%s: can't save config file - %s\n", PACKAGE, path);
		return;
	}
	g_free(path);
	
	fprintf(fp, "%s\n", VERSION);
	fprintf(fp, "%s\n", conf->useragent);
	fprintf(fp, "%s\n", conf->homepage);
	fprintf(fp, "%s\n", conf->downloaddir);
	fprintf(fp, "%d\n", conf->enableplugins);
	fprintf(fp, "%d\n", conf->enablescripts);
	fprintf(fp, "%d\n", conf->enablefileaccess);
	fprintf(fp, "%d\n", conf->strictssl);
	fprintf(fp, "%d\n", conf->enableinspector);
	fprintf(fp, "%d\n", conf->loadimages);
	fprintf(fp, "%d\n", conf->enablespatialbrowsing);
	fprintf(fp, "%d\n", conf->enablespellchecking);
	fprintf(fp, "%d\n", conf->hidebackground);
	fprintf(fp, "%d\n", conf->fullcontentzoom);
}
*/

static void
save_config_file (Conf *conf)
{
	GKeyFile *key_file;
	gchar *path;
	
	/* edit existing file or create new file */
	key_file = g_key_file_new ();
		
	g_key_file_set_string (key_file, "Default", "version", VERSION);
	g_key_file_set_string (key_file, "Default", "useragent", conf->useragent);
	g_key_file_set_string (key_file, "Default", "homepage", conf->homepage);
	g_key_file_set_string (key_file, "Default", "engine", conf->engine);
	g_key_file_set_string (key_file, "Default", "download-dir", conf->downloaddir);
	g_key_file_set_boolean (key_file, "Default", "enableplugins", conf->enableplugins);
	g_key_file_set_boolean (key_file, "Default", "enablescripts", conf->enablescripts);
	g_key_file_set_boolean (key_file, "Default", "enablefileaccess", conf->enablefileaccess);
	g_key_file_set_boolean (key_file, "Default", "strictssl", conf->strictssl);
	g_key_file_set_boolean (key_file, "Default", "enableinspector", conf->enableinspector);
	g_key_file_set_boolean (key_file, "Default", "loadimages", conf->loadimages);
	g_key_file_set_boolean (key_file, "Default", "enablespatialbrowsing", conf->enablespatialbrowsing);
	g_key_file_set_boolean (key_file, "Default", "enablespellchecking", conf->enablespellchecking);
	g_key_file_set_boolean (key_file, "Default", "hidebackground", conf->hidebackground);
	g_key_file_set_boolean (key_file, "Default", "fullcontentzoom", conf->fullcontentzoom);
	
	path = g_build_filename(g_get_user_config_dir(), PACKAGE, PACKAGE "rc", NULL);
	g_key_file_save_to_file (key_file, path, NULL);
	g_free (path);
	
	g_key_file_free (key_file);
}

static void
setup(void)
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
}

int
main (int argc, char *argv[])
{
	Conf *conf;
	Browser *b;
	
	gtk_init(&argc, &argv);
	parse_args(argc, argv);
	
	g_set_application_name("Dragonfly");
	
	setup();
	
	conf = g_malloc (sizeof (Conf));
	
	conf->useragent = USER_AGENT;
	conf->homepage = HOME_PAGE;
	conf->engine = ENGINE;
	conf->downloaddir = DOWNLOAD_DIR;
	conf->enableplugins = ENABLE_PLUGINS;
	conf->enablescripts = ENABLE_SCRIPTS;
	conf->enablefileaccess = ENABLE_FILE_ACCESS;
	conf->strictssl = STRICT_SSL;
	conf->enableinspector = ENABLE_INSPECTOR;
	conf->loadimages = LOAD_IMAGES;
	conf->enablespatialbrowsing = ENABLE_SPATIAL_BROWSING;
	conf->enablespellchecking = ENABLE_SPELL_CHECKING;
	conf->hidebackground = HIDE_BACKGROUND;
	conf->fullcontentzoom = FULL_CONTENT_ZOOM;
	
	load_config_file (conf);
	save_config_file (conf);
	
	b = browser_new (conf);
	gtk_window_set_title (GTK_WINDOW (b->window), "Dragonfly");
	
	//gchar* uri = (gchar*) (argc > 1 ? argv[1] : HOME_PAGE);
	gchar *uri = (gchar*) HOME_PAGE;
	webkit_web_view_load_uri (b->webview, uri);
	
	gtk_main();
	cleanup();
	
	return 0;
}
