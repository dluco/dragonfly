#include "dragonfly.h"

GtkEntryBuffer* search_buffer = NULL;
gboolean case_sensitive = FALSE;

void
find_next (GtkWidget* widget, Browser *b)
{
	webkit_web_view_search_text (b->webview, gtk_entry_buffer_get_text (search_buffer), case_sensitive, TRUE, TRUE);
}

/*
 * Dialog to search for text in current web-view
 */
void
search_dialog (GtkWidget* widget, Browser *b)
{
	GtkWidget *dialog;
	GtkWidget *find_button;
	GtkWidget *hbox;
	GtkWidget *find_label;
	GtkWidget *find_entry;
	GtkWidget *case_button;
	
	dialog = gtk_dialog_new_with_buttons ("Find",
													GTK_WINDOW (b->window),
													GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
													GTK_STOCK_CANCEL,
													GTK_RESPONSE_REJECT,
													GTK_STOCK_FIND,
													GTK_RESPONSE_ACCEPT,
													NULL);
	
	/* Set "Find" button as default button */
	find_button = gtk_dialog_get_widget_for_response (GTK_DIALOG (dialog), GTK_RESPONSE_ACCEPT);
	gtk_widget_set_can_default (find_button, TRUE);
	gtk_widget_grab_default (find_button);
	
	/* Create a hbox to hold label and entry */
	hbox = gtk_hbox_new (FALSE, 0);
	find_label = gtk_label_new_with_mnemonic ("Fi_nd what:");
	
	if (!search_buffer)
		search_buffer = gtk_entry_buffer_new (NULL, -1);
	
	/* Set up entry - entry activation activates the find button as well */
	find_entry = gtk_entry_new_with_buffer (GTK_ENTRY_BUFFER (search_buffer));
	gtk_entry_set_activates_default (GTK_ENTRY (find_entry), TRUE);
	gtk_label_set_mnemonic_widget (GTK_LABEL (find_label), find_entry);
	
	/* Pack label and entry into hbox */
	gtk_box_pack_start (GTK_BOX (hbox), find_label, FALSE, FALSE, 5);
	gtk_box_pack_start (GTK_BOX (hbox), find_entry, FALSE, FALSE, 5);
	
	/* Pack hbox into the content area */
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), hbox, FALSE, FALSE, 5);
	
	/* Set up toggle for matching case */
	case_button = gtk_check_button_new_with_mnemonic ("_Match case");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (case_button), case_sensitive);
	gtk_container_set_border_width (GTK_CONTAINER (case_button), 8);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox), case_button, FALSE, FALSE, 5);
	
	/* Show all widgets */
	gtk_widget_show (find_label);
	gtk_widget_show (find_entry);
	gtk_widget_show (hbox);
	gtk_widget_show (case_button);
	
	/* Run dialog and check result */
	gint result = gtk_dialog_run (GTK_DIALOG (dialog));
	switch (result)
	{
		/* "Find" button was pressed/activated - perform search */
		case GTK_RESPONSE_ACCEPT:
			webkit_web_view_search_text (b->webview,
				gtk_entry_get_text (GTK_ENTRY (find_entry)),
				gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (case_button)),
				TRUE,
				TRUE);
			break;
		/* Cancelled or closed - do nothing */
		default:
			break;
	}
	
	case_sensitive = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (case_button));

	/* Destroy the dialog */
	gtk_widget_destroy (dialog);
}
