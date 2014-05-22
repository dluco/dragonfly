#ifndef _DRAGONFLY_H
#define _DRAGONFLY_H

#include <gtk/gtk.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <webkit/webkit.h>

typedef struct SearchEngine {
	char *name;
	char *url;
} SearchEngine;

typedef struct Browser {
	GtkWidget *window;
	GtkWidget *vbox, *menubar, *toolbar, *pane, *scrolled_window;
	GtkWidget *uri_entry, *search_engine_entry;
	GtkToolItem *back_button, *forward_button, *refresh_button, *home_button;
	GtkStatusbar *status_bar;
	WebKitWebView *webview;
	WebKitWebInspector *inspector;
	gint progress;
	guint status_context_id;
	char *title;
	SearchEngine *engine;
	gboolean fullscreen, isinspecting, zoomed;
	struct Browser *next;
} Browser;

extern Browser *browsers;

#include "about.h"
#include "callback.h"
#include "browser.h"
#include "dialog.h"
#include "download.h"
#include "menu.h"
#include "search.h"
#include "toolbar.h"
#include "utils.h"

#include "config.h"

#endif /* _DRAGONFLY_H */
