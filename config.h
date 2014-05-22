#define useragent "Mozilla/5.0 (X11; U; Unix; en-US) " \
	"AppleWebKit/537.15 (KHTML, like Gecko) Chrome/24.0.1295.0 " \
	"Safari/537.15"

#define HOME_PAGE "https://duckduckgo.com/"

#define COOKIE_FILE "cookies.txt"
#define DOWNLOAD_DIR "~/Downloads/"
/* 
 * use:
 * 
 * char *download_directory = buildpath (DOWNLOAD_DIR);
 * 
 * to get the full path
 * */
 
/* Webkit default features */
#define ENABLE_SPATIAL_BROWSING FALSE
#define ENABLE_PLUGINS TRUE
#define ENABLE_SCRIPTS TRUE
#define ENABLE_FILE_ACCESS TRUE
#define ENABLE_INSPECTOR TRUE
#define LOAD_IMAGES TRUE
#define ENALBE_SPELL_CHECKING TRUE
#define HIDE_BACKGROUND  FALSE
#define FULL_CONTENT_ZOOM TRUE
