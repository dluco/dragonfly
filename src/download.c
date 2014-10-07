#include "download.h"
#include "dialog.h"

extern char *download_dir;

gboolean decide_download(WebKitWebView *view, WebKitWebFrame *frame,
	WebKitNetworkRequest *request, gchar *mimetype, 
	WebKitWebPolicyDecision *policy_decision, Browser *b)
{
	if (!webkit_web_view_can_show_mime_type(view, mimetype))
	{
		webkit_web_policy_decision_download(policy_decision);
		return TRUE;
	}
	return FALSE;
}

gboolean init_download(WebKitWebView *view, WebKitDownload *download, Browser *b)
{
	const gchar *uri, *filename;
	const gchar *pathname = NULL;
	
	filename = webkit_download_get_suggested_filename(download);
	
	pathname = save_dialog(filename, download_dir, b);
		
	if (pathname) {
		uri = g_strconcat("file://", pathname, NULL);
		webkit_download_set_destination_uri(download, uri);
		
		return TRUE;
	}
	return FALSE;
}
