#include "dragonfly.h"

/*
 * Callback for about menu item - open about dialog
 */
void
about (GtkWidget* widget, Browser *b)
{
	
	GtkWidget* about_dialog = gtk_about_dialog_new ();
	
	const gchar *authors[] = {"David Luco", "<dluco11@gmail.com>", NULL};
	
	/* Set program name and comments */
	gtk_about_dialog_set_program_name (GTK_ABOUT_DIALOG (about_dialog), "Dragonfly");
	gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG (about_dialog), "A simple webkit/gtk browser, in the style of surf and midori");
	
	/* Set logo to display in dialog */
	gtk_about_dialog_set_logo_icon_name (GTK_ABOUT_DIALOG (about_dialog), "web-browser");
	/* Set taskbar/window icon */
	gtk_window_set_icon_name (GTK_WINDOW (about_dialog), "web-browser");
	
	/* Set authors, license, and website in dialog */
	gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG (about_dialog), authors);
	gtk_about_dialog_set_license (GTK_ABOUT_DIALOG (about_dialog), "Distributed under the MIT license.\nhttp://www.opensource.org/licenses/mit-license.php");
	//gtk_about_dialog_set_website (GTK_ABOUT_DIALOG (about_dialog), "http://dluco.github.io/sb/");
	
	gtk_dialog_run (GTK_DIALOG (about_dialog));
	
	gtk_widget_destroy (about_dialog);
}
