#ifndef _CALLBACK_H
#define _CALLBACK_H

void activate_search_engine_entry (GtkWidget* entry, Browser *b);
void activate_search_engine_entry_icon (GtkEntry *entry, GtkEntryIconPosition icon_pos, GdkEvent *event, Browser *b);
void activate_uri_entry (GtkWidget *entry, Browser *b);
gboolean context_menu_popup (GtkWidget *widget, GdkEventButton *event, Browser *b);
WebKitWebView *create_window (WebKitWebView  *v, WebKitWebFrame *f, Browser *b);
void destroy_browser (Browser *b);
void destroy_window (GtkWidget *widget, Browser *b);
void fullscreen (GtkWidget *w, Browser *b);
void go_back (GtkWidget* w, Browser *b);
void go_forward (GtkWidget* w, Browser *b);
void go_home (GtkWidget *w, Browser *b);
void toggle_widget (GtkWidget *widget, gpointer data);
WebKitWebView *inspector_new (WebKitWebInspector *i, WebKitWebView *v, Browser *b);
gboolean inspector_show (WebKitWebInspector *i, Browser *b);
gboolean inspector_close (WebKitWebInspector *i, Browser *b);
void inspector_finished (WebKitWebInspector *i, Browser *b);
void inspector_toggle (GtkWidget *w, Browser *b);
void link_hover (WebKitWebView* page, const gchar* title, const gchar* link, Browser *b);
void load_status_change (WebKitWebView *view, GParamSpec *pspec, Browser *b);
void on_edit_copy (GtkWidget* widget, Browser *b);
void on_edit_cut (GtkWidget* widget, Browser *b);
void on_edit_delete (GtkWidget* widget, Browser *b);
void on_edit_paste (GtkWidget* widget, Browser *b);
void on_file_open (GtkWidget *w, Browser *b);
void on_file_print (GtkWidget *w, Browser *b);
void on_file_quit (GtkWidget *w, Browser *b);
void progress_change (WebKitWebView *view, GParamSpec *pspec, Browser *b);
void refresh (GtkWidget* w, Browser *b);
void set_search_engine(GtkWidget *w, Browser *b);
void title_change(WebKitWebView *view, WebKitWebFrame *frame, const char *title, Browser *b);
void update_browser (Browser *b);
void view_context_menu_popup (GtkWidget *widget, GdkEventButton *event,  Browser *b);
void view_source (GtkWidget *w, Browser *b);
void window_state_event(GtkWidget *w, Browser *b);
void zoom_in (GtkWidget* widget, Browser *b);
void zoom_out (GtkWidget* widget, Browser *b);
void zoom_reset (GtkWidget* widget, Browser *b);

#endif /* _CALLBACK_H */
