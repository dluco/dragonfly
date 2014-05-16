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
	guint status_context_id;
	gboolean fullscreen, isinspecting, zoomed;
	struct Browser *next;
} Browser;

extern Browser *browsers;

#include "about.h"
#include "callback.h"
#include "browser.h"
#include "menu.h"
#include "toolbar.h"

#include "config.h"

#endif /* _DRAGONFLY_H */
