#include "dragonfly.h"

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

static const gchar*
save_dialog_cb (const gchar *filename, char *directory, Browser *b)
{
	GtkWidget *dialog;
	
	dialog = gtk_file_chooser_dialog_new ("Save File",
										GTK_WINDOW (b->window),
										GTK_FILE_CHOOSER_ACTION_SAVE,
										GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
										GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
										NULL);
	
	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);
	
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (dialog), directory);
	gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), filename);
	
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
	
	gtk_widget_destroy (dialog);
	
	return filename;
}

gboolean
init_download (WebKitWebView *view, WebKitDownload *download, Browser *b)
{
	const gchar *uri, *filename;
	char *download_dir;
	
	download_dir = buildpath (DOWNLOAD_DIR);
	
	filename = save_dialog_cb (webkit_download_get_suggested_filename (download), download_dir, b);
	
	uri = g_strconcat ("file://", filename, NULL);
	webkit_download_set_destination_uri (download, uri);
	
	return TRUE;
}
