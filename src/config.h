#ifndef _CONFIG_H
#define _CONFIG_H

#define USER_AGENT "Mozilla/5.0(X11; U; Unix; en-US) " \
	"AppleWebKit/537.15(KHTML, like Gecko) Chrome/24.0.1295.0 " \
	"Safari/537.15"

#define HOME_PAGE "https://duckduckgo.com/"
#define ENGINE "Duck Duck Go"

#define COOKIE_FILE "~/.config/dragonfly/cookies.txt"
#define STYLE_FILE "~/.config/dragonfly/style.css"
#define CA_FILE "/etc/ssl/certs/ca-certificates.crt"
#define DOWNLOAD_DIR "~/Downloads/"
 
/* Webkit default features */
#define ENABLE_SPATIAL_BROWSING FALSE
#define ENABLE_PLUGINS TRUE
#define ENABLE_SCRIPTS TRUE
#define ENABLE_FILE_ACCESS TRUE
#define STRICT_SSL FALSE
#define ENABLE_INSPECTOR TRUE
#define LOAD_IMAGES TRUE
#define ENABLE_SPELL_CHECKING TRUE
#define HIDE_BACKGROUND  FALSE
#define FULL_CONTENT_ZOOM TRUE

typedef struct _config {
	gchar *useragent;
	gchar *homepage;
	gchar *engine;
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
	gboolean windowstate;
} Config;

Config *config_copy(Config *conf);
void config_create_file(gchar *pathname);
void config_init(Config *conf);
void config_load_from_file(Config *conf);
Config *config_new();
void config_save_to_file(Config *conf);

#endif /* _CONFIG_H */
