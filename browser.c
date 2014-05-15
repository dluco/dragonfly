#include "dragonfly.h"

Browser *
create_browser ()
{
	Browser *b;
	
	if (!(b = malloc (sizeof (Browser))))
	{
		fprintf (stderr, "Error: Failed to allocate memory\n");
	}
	
	b->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_wmclass (GTK_WINDOW (b->window), "dragonfly", "Dragonfly");
	gtk_window_set_role (GTK_WINDOW (b->window), "Dragonfly");
	gtk_window_set_icon_name (GTK_WINDOW (b->window), "web-browser");
	
	gtk_window_set_default_size (GTK_WINDOW (b->window), 800, 600);
	
	g_signal_connect (G_OBJECT (b->window),
		"destroy",
		G_CALLBACK (destroy_window), b);
	
	/* Pane */
	b->pane = gtk_vpaned_new ();
	
	/* VBox */
	b->vbox = gtk_vbox_new (FALSE, 0);
	gtk_paned_pack1 (GTK_PANED (b->pane), b->vbox, TRUE, TRUE);
	
	/* Scrolled Window */
	b->scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (b->scrolled_window),
		GTK_POLICY_NEVER, GTK_POLICY_NEVER);
	
	/* Webview */
	b->webview = WEBKIT_WEB_VIEW (webkit_web_view_new ());
	g_signal_connect (G_OBJECT (b->webview),
		"create-web-view",
		G_CALLBACK (create_window), b);
	g_signal_connect (G_OBJECT (b->webview),
		"hovering-over-link",
		G_CALLBACK (link_hover), b);
	
	/* Statusbar */
	b->status_bar = GTK_STATUSBAR (gtk_statusbar_new ());
	b->status_context_id = gtk_statusbar_get_context_id (b->status_bar, "Link Hover");
	
	/* Arrange containers */
	gtk_container_add (GTK_CONTAINER (b->scrolled_window), GTK_WIDGET (b->webview));
	gtk_container_add (GTK_CONTAINER (b->window), b->pane);
	gtk_box_pack_start (GTK_BOX (b->vbox), b->scrolled_window, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (b->vbox), GTK_WIDGET (b->status_bar), FALSE, FALSE, 0);
	
	/* Setup */
	gtk_box_set_child_packing (GTK_BOX (b->vbox), b->scrolled_window, TRUE,
		TRUE, 0, GTK_PACK_START);
	gtk_widget_grab_focus (GTK_WIDGET (b->webview));
	gtk_widget_show (b->pane);
	gtk_widget_show (b->vbox);
	gtk_widget_show (b->scrolled_window);
	gtk_widget_show (GTK_WIDGET (b->webview));
	gtk_widget_show (GTK_WIDGET (b->status_bar));
	gtk_widget_show (b->window);
	
	b->next = browsers;
	browsers = b;
	
	gtk_widget_show (b->window);
	
	return b;
}
