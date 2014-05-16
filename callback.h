#ifndef _CALLBACK_H
#define _CALLBACK_H

WebKitWebView *create_window (WebKitWebView  *v, WebKitWebFrame *f, Browser *b);
void destroy_browser (Browser *b);
void destroy_window (GtkWidget *widget, Browser *b);
void go_back (GtkWidget* w, Browser *b);
void go_forward (GtkWidget* w, Browser *b);
void go_home (GtkWidget *w, Browser *b);
WebKitWebView *inspector_new (WebKitWebInspector *i, WebKitWebView *v, Browser *b);
gboolean inspector_show (WebKitWebInspector *i, Browser *b);
gboolean inspector_close (WebKitWebInspector *i, Browser *b);
void inspector_finished (WebKitWebInspector *i, Browser *b);
void inspector_toggle (GtkWidget *w, Browser *b);
void link_hover (WebKitWebView* page, const gchar* title, const gchar* link, Browser *b);
void on_edit_copy (GtkWidget* widget, Browser *b);
void on_edit_cut (GtkWidget* widget, Browser *b);
void on_edit_delete (GtkWidget* widget, Browser *b);
void on_edit_paste (GtkWidget* widget, Browser *b);
void on_file_open (GtkWidget *w, Browser *b);
void on_file_print (GtkWidget *w, Browser *b);
void on_file_quit (GtkWidget *w, Browser *b);
void fullscreen (GtkWidget *w, Browser *b);
void refresh (GtkWidget* w, Browser *b);
void view_source (GtkWidget *w, Browser *b);
void zoom_in (GtkWidget* widget, Browser *b);
void zoom_out (GtkWidget* widget, Browser *b);
void zoom_reset (GtkWidget* widget, Browser *b);

#endif /* _CALLBACK_H */
