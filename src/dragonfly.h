#ifndef _DRAGONFLY_H
#define _DRAGONFLY_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <webkit/webkit.h>

typedef struct SearchEngine_t {
	char *name;
	char *text;
	char *url;
	struct SearchEngine_t *next;
} SearchEngine;

typedef struct conf_t {
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
} Conf;

typedef struct Browser_t {
	GtkWidget *window;
	GtkWidget *vbox, *menubar, *toolbar, *pane, *scrolled_window;
	GtkWidget *uri_entry, *search_engine_entry;
	GtkWidget *engine_menu;
	GtkToolItem *back_button, *forward_button, *refresh_button, *home_button;
	GtkStatusbar *status_bar;
	WebKitWebView *webview;
	WebKitWebInspector *inspector;
	gint progress;
	guint status_context_id;
	SearchEngine *engine;
	Conf *conf;
	char *title;
	gboolean fullscreen, isinspecting, maximized, zoomed;
	struct Browser_t *next;
} Browser;

extern Browser *browsers;
extern SearchEngine *engine_list;
extern char *cookiefile;

#include "about.h"
#include "callback.h"
#include "config.h"
#include "cookie.h"
#include "browser.h"
#include "dialog.h"
#include "download.h"
#include "menu.h"
#include "search.h"
#include "searchengine.h"
#include "toolbar.h"
#include "utils.h"

/* start config.h */
#define USER_AGENT "Mozilla/5.0 (X11; U; Unix; en-US) " \
	"AppleWebKit/537.15 (KHTML, like Gecko) Chrome/24.0.1295.0 " \
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

/* end config.h */

#define BUFSIZE 1024

#endif /* _DRAGONFLY_H */
