#include "dragonfly.h"
#include <string.h>

Conf *
conf_copy(Conf *conf)
{
	Conf *temp;
	
	temp = conf_new();
	
	temp->useragent = g_strdup(conf->useragent);
	temp->homepage = g_strdup(conf->homepage);
	temp->engine = g_strdup(conf->engine);
	temp->downloaddir = g_strdup(conf->downloaddir);
	temp->enableplugins = conf->enableplugins;
	temp->enablescripts = conf->enablescripts;
	temp->enablefileaccess = conf->enablefileaccess;
	temp->strictssl = conf->strictssl;
	temp->enableinspector = conf->enableinspector;
	temp->loadimages = conf->loadimages;
	temp->enablespatialbrowsing = conf->enablespatialbrowsing;
	temp->enablespellchecking = conf->enablespellchecking;
	temp->hidebackground = conf->hidebackground;
	temp->fullcontentzoom = conf->fullcontentzoom;
	temp->windowstate = conf->windowstate;
	
	return temp;
}

void
conf_create_file(gchar *pathname)
{
	GKeyFile *key_file;
	
	key_file = g_key_file_new();
	
	g_key_file_set_string(key_file, "Default", "version", VERSION);
	g_key_file_set_string(key_file, "Default", "useragent", USER_AGENT);
	g_key_file_set_string(key_file, "Default", "homepage", HOME_PAGE);
	g_key_file_set_string(key_file, "Default", "download-dir", DOWNLOAD_DIR);
	g_key_file_set_boolean(key_file, "Default", "enableplugins", ENABLE_PLUGINS);
	g_key_file_set_boolean(key_file, "Default", "enablescripts", ENABLE_SCRIPTS);
	g_key_file_set_boolean(key_file, "Default", "enablefileaccess", ENABLE_FILE_ACCESS);
	g_key_file_set_boolean(key_file, "Default", "strictssl", STRICT_SSL);
	g_key_file_set_boolean(key_file, "Default", "enableinspector", ENABLE_INSPECTOR);
	g_key_file_set_boolean(key_file, "Default", "loadimages", LOAD_IMAGES);
	g_key_file_set_boolean(key_file, "Default", "enablespatialbrowsing", ENABLE_SPATIAL_BROWSING);
	g_key_file_set_boolean(key_file, "Default", "enablespellchecking", ENABLE_SPELL_CHECKING);
	g_key_file_set_boolean(key_file, "Default", "hidebackground", HIDE_BACKGROUND);
	g_key_file_set_boolean(key_file, "Default", "fullcontentzoom", FULL_CONTENT_ZOOM);
	g_key_file_set_boolean(key_file, "Default", "windowstate", FALSE);
	
	g_key_file_save_to_file(key_file, pathname, NULL);
	
	g_key_file_free(key_file);
}

void
conf_load_from_file(Conf *conf)
{
	GKeyFile *key_file;
	gchar *path;
	
	path = g_build_filename(g_get_user_config_dir(), PACKAGE, PACKAGE "rc", NULL);
	/* check if file exists */
	if (!g_file_test(path, G_FILE_TEST_EXISTS)) {
		/* config file does not exist - create with defaults */
		fprintf(stderr, "%s: config file does not exist, creating\n", PACKAGE);
		conf_create_file(path);
	}
	
	key_file = g_key_file_new ();
	g_key_file_load_from_file (key_file, path, G_KEY_FILE_KEEP_COMMENTS, NULL);
	g_free (path);
	
	conf->useragent = g_key_file_get_string(key_file, "Default", "useragent", NULL);
	conf->homepage = g_key_file_get_string(key_file, "Default", "homepage", NULL);
	conf->engine = g_key_file_get_string(key_file, "Default", "engine", NULL);
	conf->downloaddir = g_key_file_get_string(key_file, "Default", "download-dir", NULL);
	conf->enableplugins = g_key_file_get_boolean(key_file, "Default", "enableplugins", NULL);
	conf->enablescripts = g_key_file_get_boolean(key_file, "Default", "enablescripts", NULL);
	conf->enablefileaccess = g_key_file_get_boolean(key_file, "Default", "enablefileaccess", NULL);
	conf->strictssl = g_key_file_get_boolean(key_file, "Default", "strictssl", NULL);
	conf->enableinspector = g_key_file_get_boolean(key_file, "Default", "enableinspector", NULL);
	conf->loadimages = g_key_file_get_boolean(key_file, "Default", "loadimages", NULL);
	conf->enablespatialbrowsing = g_key_file_get_boolean(key_file, "Default", "enablespatialbrowsing", NULL);
	conf->enablespellchecking = g_key_file_get_boolean(key_file, "Default", "enablespellchecking", NULL);
	conf->hidebackground = g_key_file_get_boolean(key_file, "Default", "hidebackground", NULL);
	conf->fullcontentzoom = g_key_file_get_boolean(key_file, "Default", "fullcontentzoom", NULL);
	conf->windowstate = g_key_file_get_boolean(key_file, "Default", "windowstate", NULL);
	
	g_key_file_free (key_file);
}

Conf *
conf_new()
{
	Conf *conf;
	
	if (!(conf = malloc(sizeof(*conf)))) {
		fprintf(stderr, "%s: failed to allocate memory\n", PACKAGE);
		return NULL;
	}
	return conf;
}

void
conf_save_to_file(Conf *conf)
{
	GKeyFile *key_file;
	gchar *path;
	
	/* edit existing file or create new file */
	key_file = g_key_file_new();
		
	g_key_file_set_string(key_file, "Default", "version", VERSION);
	g_key_file_set_string(key_file, "Default", "useragent", conf->useragent);
	g_key_file_set_string(key_file, "Default", "homepage", conf->homepage);
	g_key_file_set_string(key_file, "Default", "engine", conf->engine);
	g_key_file_set_string(key_file, "Default", "download-dir", conf->downloaddir);
	g_key_file_set_boolean(key_file, "Default", "enableplugins", conf->enableplugins);
	g_key_file_set_boolean(key_file, "Default", "enablescripts", conf->enablescripts);
	g_key_file_set_boolean(key_file, "Default", "enablefileaccess", conf->enablefileaccess);
	g_key_file_set_boolean(key_file, "Default", "strictssl", conf->strictssl);
	g_key_file_set_boolean(key_file, "Default", "enableinspector", conf->enableinspector);
	g_key_file_set_boolean(key_file, "Default", "loadimages", conf->loadimages);
	g_key_file_set_boolean(key_file, "Default", "enablespatialbrowsing", conf->enablespatialbrowsing);
	g_key_file_set_boolean(key_file, "Default", "enablespellchecking", conf->enablespellchecking);
	g_key_file_set_boolean(key_file, "Default", "hidebackground", conf->hidebackground);
	g_key_file_set_boolean(key_file, "Default", "fullcontentzoom", conf->fullcontentzoom);
	g_key_file_set_boolean(key_file, "Default", "windowstate", conf->windowstate);
	
	path = g_build_filename(g_get_user_config_dir(), PACKAGE, PACKAGE "rc", NULL);
	g_key_file_save_to_file(key_file, path, NULL);
	if (!g_file_test(path, G_FILE_TEST_EXISTS)) {
		fprintf(stderr, "%s: error saving config file\n", PACKAGE);
	}
	g_free(path);
	
	g_key_file_free(key_file);
}

void
conf_init(Conf *conf)
{
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
	conf->windowstate = FALSE;
}
