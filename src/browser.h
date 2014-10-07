#ifndef _BROWSER_H
#define _BROWSER_H

#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include "config.h"
#include "searchengine.h"

typedef struct _browser {
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
	struct _browser *next;
} Browser;

SearchEngine *browser_get_default_search_engine(Browser *b);
void browser_set_default_search_engine(Browser *b, SearchEngine *engine);
void browser_set_settings(Browser *b, Config *conf);
Browser *browser_new(Config *conf);

#endif /* _BROWSER_H */
