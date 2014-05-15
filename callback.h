#ifndef _CALLBACK_H
#define _CALLBACK_H

WebKitWebView *create_window (WebKitWebView  *v, WebKitWebFrame *f, Browser *b);
void destroy_browser (Browser *b);
void destroy_window (GtkWidget *widget, Browser *b);
WebKitWebView *inspector_new (WebKitWebInspector *i, WebKitWebView *v, Browser *b);
gboolean inspector_show (WebKitWebInspector *i, Browser *b);
gboolean inspector_close (WebKitWebInspector *i, Browser *b);
void inspector_finished (WebKitWebInspector *i, Browser *b);
void link_hover (WebKitWebView* page, const gchar* title, const gchar* link, Browser *b);
void on_file_open (GtkWidget *w, gpointer data);
void on_file_print (GtkWidget *w, gpointer data);
void on_file_quit (GtkWidget *w, gpointer data);

#endif /* _CALLBACK_H */
