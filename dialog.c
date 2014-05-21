#include "dragonfly.h"

#include <stdarg.h>

void
run_dialog_message (GtkWidget *window, GtkMessageType type, gchar *message, ...)
{
	va_list ap;
	GtkWidget *dialog;
	gchar *str;
	
	va_start (ap, message);
		str = g_strdup_printf (message, ap);
	va_end (ap);
	
	dialog = gtk_message_dialog_new (GTK_WINDOW (window),
		GTK_DIALOG_DESTROY_WITH_PARENT,
		type,
		GTK_BUTTONS_NONE,
		str);
		
	gtk_window_set_resizable (GTK_WINDOW (dialog), FALSE);
	gtk_dialog_add_buttons (GTK_DIALOG (dialog), GTK_STOCK_OK, GTK_RESPONSE_CANCEL, NULL);
	gtk_dialog_set_default_response (GTK_DIALOG (dialog), GTK_RESPONSE_CANCEL);
	g_free (str);
	
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}

const gchar *
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
