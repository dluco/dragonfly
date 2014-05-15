#ifndef _DRAGONFLY_H
#define _DRAGONFLY_H

#include <gtk/gtk.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <webkit/webkit.h>

typedef struct Browser {
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *pane;
	GtkWidget *scrolled_window;
	GtkStatusbar *status_bar;
	WebKitWebView *webview;
	guint status_context_id;
	struct Browser *next;
	gboolean zoomed, fullscreen;
} Browser;

/*static Browser *browsers = NULL;*/
extern Browser *browsers;

#include "browser.h"
#include "callback.h"

#endif /* _DRAGONFLY_H */
