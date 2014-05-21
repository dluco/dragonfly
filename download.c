#include "dragonfly.h"

extern char *download_dir;

gboolean
decide_download (WebKitWebView *view, WebKitWebFrame *frame, WebKitNetworkRequest *request, gchar *mimetype,  WebKitWebPolicyDecision *policy_decision, Browser *b)
{
	if (!webkit_web_view_can_show_mime_type (view, mimetype))
	{
		webkit_web_policy_decision_download (policy_decision);
		return TRUE;
	}
	return FALSE;
}

static const gchar *
save_dialog (const gchar *filename, char *directory, Browser *b)
{
	GtkWidget *dialog;
	gint result;
	gchar *pathname;
	
	dialog = gtk_file_chooser_dialog_new ("Save File",
										GTK_WINDOW (b->window),
										GTK_FILE_CHOOSER_ACTION_SAVE,
										GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
										GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
										NULL);
	
	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);
	
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (dialog), directory);
	gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), filename);
	
	result = gtk_dialog_run (GTK_DIALOG (dialog));
	switch (result) {
		case GTK_RESPONSE_ACCEPT:
			pathname = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
			break;
		default:
			pathname = NULL;
			break;
	}
	
	gtk_widget_destroy (dialog);
	
	return pathname;
}

gboolean
init_download (WebKitWebView *view, WebKitDownload *download, Browser *b)
{
	const gchar *uri, *filename;
	const gchar *pathname = NULL;
	//char *download_dir;
	
	//download_dir = buildpath (DOWNLOAD_DIR);
	filename = webkit_download_get_suggested_filename (download);
	
	pathname = save_dialog (filename, download_dir, b);
	
	//g_free (download_dir);
	
	if (pathname) {
		uri = g_strconcat ("file://", pathname, NULL);
		webkit_download_set_destination_uri (download, uri);
		
		return TRUE;
	}
	return FALSE;
}
