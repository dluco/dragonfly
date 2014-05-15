#ifndef _DRAGONFLY_H
#define _DRAGONFLY_H

#include <gtk/gtk.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <webkit/webkit.h>

typedef struct Browser {
	GtkWidget *window;
	GtkWidget *vbox, *menubar, *pane, *scrolled_window;
	GtkStatusbar *status_bar;
	WebKitWebView *webview;
	WebKitWebInspector *inspector;
	guint status_context_id;
	gboolean fullscreen, isinspecting, zoomed;
	struct Browser *next;
} Browser;

extern Browser *browsers;

#include "callback.h"
#include "browser.h"
#include "menu.h"

#endif /* _DRAGONFLY_H */
