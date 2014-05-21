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
