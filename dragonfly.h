#ifndef _DRAGONFLY_H
#define _DRAGONFLY_H

#include <gtk/gtk.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <webkit/webkit.h>

typedef struct Browser {
	GtkWidget *window;
	GtkWidget *vbox, *menubar, *toolbar, *pane, *scrolled_window;
	GtkWidget *uri_entry;
	GtkWidget *search_engine_entry;
	GtkStatusbar *status_bar;
	WebKitWebView *webview;
	WebKitWebInspector *inspector;
	//GtkAccelGroup *accel_group;
	gint progress;
	guint status_context_id;
	char *title;
	gboolean fullscreen, isinspecting, zoomed;
	struct Browser *next;
} Browser;

extern Browser *browsers;
//extern char *download_dir;

#include "about.h"
#include "callback.h"
#include "browser.h"
#include "download.h"
#include "menu.h"
#include "search.h"
#include "toolbar.h"
#include "utils.h"

#include "config.h"

#endif /* _DRAGONFLY_H */
