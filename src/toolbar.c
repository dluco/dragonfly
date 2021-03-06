#include <gdk/gdkkeysyms.h>
#include "toolbar.h"
#include "callback.h"
#include "dialog.h"

GtkWidget *create_toolbar(Browser *b)
{
	GtkWidget *toolbar;
	GtkAccelGroup *accel_group;
	GtkToolItem *item;
	GtkWidget *h_paned;
	
	toolbar = gtk_toolbar_new();

	/* Create accelgroup */
	accel_group = gtk_accel_group_new();

	gtk_toolbar_set_orientation(GTK_TOOLBAR(toolbar), GTK_ORIENTATION_HORIZONTAL);
	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_BOTH_HORIZ);

	/* the back button */
	b->back_button = gtk_tool_button_new_from_stock(GTK_STOCK_GO_BACK);
	gtk_widget_set_tooltip_text(GTK_WIDGET(b->back_button), "Go back to the previous page");
	g_signal_connect(G_OBJECT(b->back_button), "clicked", G_CALLBACK(go_back), b);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), GTK_TOOL_ITEM(b->back_button), -1);

	/* The forward button */
	b->forward_button = gtk_tool_button_new_from_stock(GTK_STOCK_GO_FORWARD);
	gtk_widget_set_tooltip_text(GTK_WIDGET(b->forward_button), "Go to the next page");
	g_signal_connect(G_OBJECT(b->forward_button), "clicked", G_CALLBACK(go_forward), b);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), GTK_TOOL_ITEM(b->forward_button), -1);
	
	/* The refresh button */
	b->refresh_button = gtk_tool_button_new_from_stock(GTK_STOCK_REFRESH);
	gtk_widget_set_tooltip_text(GTK_WIDGET(b->refresh_button), "Reload the current page");
	g_signal_connect(G_OBJECT(b->refresh_button), "clicked", G_CALLBACK(refresh), b);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), GTK_TOOL_ITEM(b->refresh_button), -1);
	
	/* The cancel button
	cancel_button = gtk_tool_button_new_from_stock(GTK_STOCK_CANCEL);
	gtk_widget_set_tooltip_text(GTK_WIDGET(cancel_button), "Cancel loading the current page");
	g_signal_connect(G_OBJECT(cancel_button), "clicked", G_CALLBACK(cancel_cb), NULL);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), GTK_TOOL_ITEM(cancel_button), -1); */
	
	/* The URL entry */
	b->uri_entry = gtk_entry_new();
	gtk_widget_set_tooltip_text(GTK_WIDGET(b->uri_entry), "Load a url");
	g_signal_connect(G_OBJECT(b->uri_entry), "activate", G_CALLBACK(activate_uri_entry), b);
	
	/* The search-engine entry */
	b->search_engine_entry = gtk_entry_new();
	gtk_entry_set_icon_from_stock(GTK_ENTRY(b->search_engine_entry), GTK_ENTRY_ICON_PRIMARY, GTK_STOCK_FILE);
	gtk_entry_set_icon_from_stock(GTK_ENTRY(b->search_engine_entry), GTK_ENTRY_ICON_SECONDARY, GTK_STOCK_FIND);
	gtk_widget_set_tooltip_text(GTK_WIDGET(b->search_engine_entry), "Run a web search");
	gtk_entry_set_icon_tooltip_text(GTK_ENTRY(b->search_engine_entry), GTK_ENTRY_ICON_PRIMARY, "Choose search engine");
	gtk_entry_set_icon_tooltip_text(GTK_ENTRY(b->search_engine_entry), GTK_ENTRY_ICON_SECONDARY, "Search");
	g_signal_connect(G_OBJECT(b->search_engine_entry), "activate", G_CALLBACK(activate_search_engine_entry), b);
	g_signal_connect(G_OBJECT(b->search_engine_entry), "icon-press", G_CALLBACK(activate_search_engine_entry_icon), b);

	/* Paned widget to hold uri entry and search-engine entry */
	h_paned = gtk_hpaned_new();
	gtk_paned_pack1(GTK_PANED(h_paned), b->uri_entry, TRUE, TRUE);
	gtk_paned_pack2(GTK_PANED(h_paned), b->search_engine_entry, FALSE, TRUE);
	
	item = gtk_tool_item_new();
	gtk_tool_item_set_expand(item, TRUE);
	gtk_container_add(GTK_CONTAINER(item), h_paned);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1);
	
	/* The home button */
	b->home_button = gtk_tool_button_new_from_stock(GTK_STOCK_HOME);
	gtk_widget_set_tooltip_text(GTK_WIDGET(b->home_button), "Go to home page");
	g_signal_connect(G_OBJECT(b->home_button), "clicked", G_CALLBACK(go_home), b);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), b->home_button, -1);
	
	/* Set up accelerators(keyboard shortcuts) */
	gtk_widget_add_accelerator(GTK_WIDGET(b->back_button), "clicked", accel_group, GDK_Left, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
	
	/* Set up right-click context menu */
	g_signal_connect(GTK_OBJECT(toolbar), "button-press-event", G_CALLBACK(context_menu_popup), b);
	
	/* Show widgets */
	gtk_widget_show(GTK_WIDGET(b->back_button));
	gtk_widget_show(GTK_WIDGET(b->forward_button));
	gtk_widget_show(GTK_WIDGET(b->refresh_button));
	gtk_widget_show(b->uri_entry);
	gtk_widget_show(b->search_engine_entry);
	gtk_widget_show(GTK_WIDGET(item));
	gtk_widget_show(GTK_WIDGET(h_paned));
	gtk_widget_show(GTK_WIDGET(b->home_button));

	return toolbar;
}
