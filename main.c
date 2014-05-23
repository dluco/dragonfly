#include "dragonfly.h"

typedef struct {
	gchar *useragent;
	gchar *homepage;
	gchar *downloaddir;
	gboolean enableplugins;
	gboolean enablescripts;
	gboolean enablefileaccess;
	gboolean strictssl;
	gboolean enableinspector;
	gboolean loadimages;
	gboolean enablespatialbrowsing;
	gboolean enablespellchecking;
	gboolean hidebackground;
	gboolean fullcontentzoom;
} Conf;

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
load_config_file(Conf *conf)
{
	FILE *fp;
	gchar *path;
	gchar buf[BUFSIZE];
	/*gchar **num; used for checking program version (line 1 in config file) */
	
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
	Conf *conf;
	Browser *b;
	
	//parse_args ();
	gtk_init (&argc, &argv);
	g_set_application_name("Dragonfly");
	
	setup ();
	
	conf = g_malloc (sizeof (Conf));
	
	conf->useragent = USER_AGENT;
	conf->homepage = HOME_PAGE;
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
		
	if (argc > 1)
		if (argv[1][1] == 'v') {
			printf ("Dragonfly-"VERSION", 2014 David Luco\n");
			return 0;
		}
	
	b = browser_new ();
	gtk_window_set_title (GTK_WINDOW (b->window), "Dragonfly");
	
	gchar* uri = (gchar*) (argc > 1 ? argv[1] : HOME_PAGE);
	webkit_web_view_load_uri (b->webview, uri);
	
	gtk_main ();
	cleanup ();
	
	return 0;
}
