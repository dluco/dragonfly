#ifndef _CALLBACK_H
#define _CALLBACK_H

WebKitWebView *create_window (WebKitWebView  *v, WebKitWebFrame *f, Browser *b);
void destroy_browser (Browser *b);
void destroy_window (GtkWidget *widget, Browser *b);
void link_hover (WebKitWebView* page, const gchar* title, const gchar* link, Browser *b);

#endif /* _CALLBACK_H */
