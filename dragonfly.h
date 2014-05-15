#ifndef _DRAGONFLY_H
#define _DRAGONFLY_H

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>

/*#include "config.h"*/

typedef struct Browser {
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *pane;
	GtkWidget *scrolled_window;
	WebKitWebView *webview;
	struct Browser *next;
	gboolean zoomed, fullscreen;
} Browser;

/*static Browser *browsers = NULL;*/
extern Browser *browsers;

#include "browser.h"
#include "callback.h"

#endif /* _DRAGONFLY_H */
