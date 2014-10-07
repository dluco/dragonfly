#ifndef _DOWNLOAD_H
#define _DOWNLOAD_H

#include <glib.h>
#include <webkit/webkit.h>
#include "browser.h"

gboolean decide_download(WebKitWebView *view, WebKitWebFrame *frame,
	WebKitNetworkRequest *request, gchar *mimetype,
	WebKitWebPolicyDecision *policy, Browser *b);
gboolean init_download(WebKitWebView *view, WebKitDownload *download, Browser *b);

#endif /* _DOWNLOAD_H */
