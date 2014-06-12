#ifndef _DRAGONFLY_H
#define _DRAGONFLY_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <webkit/webkit.h>

typedef struct SearchEngine {
	char *name;
	char *text;
	char *url;
	struct SearchEngine *next;
} SearchEngine;

typedef struct Browser {
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
	char *title;
	gboolean fullscreen, isinspecting, zoomed;
	struct Browser *next;
} Browser;

extern Browser *browsers;
extern SearchEngine *engine_list;
extern char *cookiefile;

#include "about.h"
#include "callback.h"
#include "cookie.h"
#include "browser.h"
#include "dialog.h"
#include "download.h"
#include "menu.h"
#include "search.h"
#include "toolbar.h"
#include "utils.h"

#include "config.h"

#define BUFSIZE 1024

#endif /* _DRAGONFLY_H */
