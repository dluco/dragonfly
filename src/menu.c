#include <gdk/gdkkeysyms.h>
#include "menu.h"
#include "callback.h"
#include "dialog.h"
#include "search.h"

extern SearchEngine *engine_list;

GtkWidget *create_menubar(Browser *b)
{
	GtkWidget *menubar;
	GtkAccelGroup *accel_group;
	
	GtkWidget *file_item;
	GtkWidget *edit_item;
	GtkWidget *view_item;
	GtkWidget *tools_item;
	GtkWidget *help_item;
	
	GtkWidget *file_menu;
	GtkWidget *edit_menu;
	GtkWidget *view_menu;
	GtkWidget *tools_menu;
	GtkWidget *help_menu;
	
	GtkWidget *open_item;
	GtkWidget *print_item;
	GtkWidget *quit_item;
	GtkWidget *cut_item;
	GtkWidget *copy_item;
	GtkWidget *paste_item;
	GtkWidget *delete_item;
	GtkWidget *find_item;
	GtkWidget *find_next_item;
	GtkWidget *zoom_in_item;
	GtkWidget *zoom_out_item;
	GtkWidget *zoom_reset_item;
	GtkWidget *fullscreen_item;
	GtkWidget *settings_item;
	GtkWidget *inspector_item;
	GtkWidget *source_item;
	GtkWidget *about_item;
	
	GtkWidget *separator;
	
	/* Create menubar */
	menubar = gtk_menu_bar_new();
	
	/* Create accelgroup */
	accel_group = gtk_accel_group_new();
	
	/* Create entries in menubar */
	file_item = gtk_menu_item_new_with_mnemonic("_File");
	edit_item = gtk_menu_item_new_with_mnemonic("_Edit");
	view_item = gtk_menu_item_new_with_mnemonic("_View");
	tools_item = gtk_menu_item_new_with_mnemonic("_Tools");
	help_item = gtk_menu_item_new_with_mnemonic("_Help");
	
	/* Create File, Edit, and Help Menus */
	file_menu = gtk_menu_new();
	edit_menu = gtk_menu_new();
	view_menu = gtk_menu_new();
	tools_menu = gtk_menu_new();
	help_menu = gtk_menu_new();
	
	/* Create the menu items(and set icons) */
	open_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, accel_group);
	gtk_menu_item_set_label(GTK_MENU_ITEM(open_item), "_Open");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(open_item), TRUE);
	print_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_PRINT, accel_group);
	gtk_menu_item_set_label(GTK_MENU_ITEM(print_item), "_Print");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(print_item), TRUE);
	quit_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accel_group);
	gtk_menu_item_set_label(GTK_MENU_ITEM(quit_item), "_Quit");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(quit_item), TRUE);
	cut_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_CUT, accel_group);
	gtk_menu_item_set_label(GTK_MENU_ITEM(cut_item), "Cu_t");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(cut_item), TRUE);
	copy_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_COPY, accel_group);
	gtk_menu_item_set_label(GTK_MENU_ITEM(copy_item), "_Copy");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(copy_item), TRUE);
	paste_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_PASTE, accel_group);
	gtk_menu_item_set_label(GTK_MENU_ITEM(paste_item), "_Paste");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(paste_item), TRUE);
	delete_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_DELETE, accel_group);
	gtk_menu_item_set_label(GTK_MENU_ITEM(delete_item), "_Delete");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(delete_item), TRUE);
	find_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_FIND, accel_group);
	gtk_menu_item_set_label(GTK_MENU_ITEM(find_item), "_Find...");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(find_item), TRUE);
	find_next_item = gtk_menu_item_new_with_mnemonic("Find _Next");
	zoom_in_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_ZOOM_IN, accel_group);
	gtk_menu_item_set_label(GTK_MENU_ITEM(zoom_in_item), "Zoom _In");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(zoom_in_item), TRUE);
	zoom_out_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_ZOOM_OUT, accel_group);
	gtk_menu_item_set_label(GTK_MENU_ITEM(zoom_out_item), "Zoom _Out");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(zoom_out_item), TRUE);
	zoom_reset_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_ZOOM_100, accel_group);
	gtk_menu_item_set_label(GTK_MENU_ITEM(zoom_reset_item), "_Reset Zoom");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(zoom_reset_item), TRUE);
	fullscreen_item = gtk_check_menu_item_new_with_label("_Fullscreen");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(fullscreen_item), TRUE);
	settings_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_PREFERENCES, NULL);
	gtk_menu_item_set_label(GTK_MENU_ITEM(settings_item), "_Settings");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(settings_item), TRUE);
	inspector_item = gtk_check_menu_item_new_with_label("_Inspector");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(inspector_item), TRUE);
	source_item = gtk_check_menu_item_new_with_label("_Page Source");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(source_item), TRUE);
	about_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT, NULL);
	gtk_menu_item_set_label(GTK_MENU_ITEM(about_item), "_About");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(about_item), TRUE);
	
	/* Set up accelerators */
	gtk_widget_add_accelerator(open_item, "activate", GTK_ACCEL_GROUP(accel_group),  GDK_o, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(print_item, "activate", GTK_ACCEL_GROUP(accel_group),  GDK_p, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(quit_item, "activate", GTK_ACCEL_GROUP(accel_group),  GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	
	gtk_widget_add_accelerator(cut_item, "activate", GTK_ACCEL_GROUP(accel_group),  GDK_x, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(copy_item, "activate", GTK_ACCEL_GROUP(accel_group),  GDK_c, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(paste_item, "activate", GTK_ACCEL_GROUP(accel_group),  GDK_v, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(delete_item, "activate", GTK_ACCEL_GROUP(accel_group),  GDK_Delete, 0, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(find_item, "activate", GTK_ACCEL_GROUP(accel_group),  GDK_f, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(find_next_item, "activate", GTK_ACCEL_GROUP(accel_group),  GDK_g, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	
	gtk_widget_add_accelerator(zoom_in_item, "activate", GTK_ACCEL_GROUP(accel_group),  GDK_plus, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(zoom_out_item, "activate", GTK_ACCEL_GROUP(accel_group),  GDK_minus, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(zoom_reset_item, "activate", GTK_ACCEL_GROUP(accel_group),  GDK_0, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(fullscreen_item, "activate", GTK_ACCEL_GROUP(accel_group),  GDK_F11, 0, GTK_ACCEL_VISIBLE);
	
	gtk_widget_add_accelerator(inspector_item, "activate", GTK_ACCEL_GROUP(accel_group),  GDK_I, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	
	/* Add menu items to the appropriate menu */
	gtk_menu_append(GTK_MENU(file_menu), open_item);
	gtk_menu_append(GTK_MENU(file_menu), print_item);
	separator = gtk_separator_menu_item_new();
	gtk_menu_append(GTK_MENU(file_menu), separator);
	gtk_widget_show(GTK_WIDGET(separator));
	gtk_menu_append(GTK_MENU(file_menu), quit_item);
	
	gtk_menu_append(GTK_MENU(edit_menu), cut_item);
	gtk_menu_append(GTK_MENU(edit_menu), copy_item);
	gtk_menu_append(GTK_MENU(edit_menu), paste_item);
	gtk_menu_append(GTK_MENU(edit_menu), delete_item);
	separator = gtk_separator_menu_item_new();
	gtk_menu_append(GTK_MENU(edit_menu), separator);
	gtk_widget_show(GTK_WIDGET(separator));
	gtk_menu_append(GTK_MENU(edit_menu), find_item);
	gtk_menu_append(GTK_MENU(edit_menu), find_next_item);
	
	gtk_menu_append(GTK_MENU(view_menu), zoom_in_item);
	gtk_menu_append(GTK_MENU(view_menu), zoom_out_item);
	gtk_menu_append(GTK_MENU(view_menu), zoom_reset_item);
	separator = gtk_separator_menu_item_new();
	gtk_menu_append(GTK_MENU(view_menu), separator);
	gtk_widget_show(GTK_WIDGET(separator));
	gtk_menu_append(GTK_MENU(view_menu), fullscreen_item);
	
	gtk_menu_append(GTK_MENU(tools_menu), settings_item);
	gtk_menu_append(GTK_MENU(tools_menu), inspector_item);
	gtk_menu_append(GTK_MENU(tools_menu), source_item);
	
	gtk_menu_append(GTK_MENU(help_menu), about_item);
	
	/* Attach the callback functions to the activate signals */
	g_signal_connect(G_OBJECT(open_item), "activate", G_CALLBACK(on_file_open), b);
	g_signal_connect(G_OBJECT(print_item), "activate", G_CALLBACK(on_file_print), b);
	g_signal_connect(G_OBJECT(quit_item), "activate", G_CALLBACK(on_file_quit), b);
	g_signal_connect(G_OBJECT(cut_item), "activate", G_CALLBACK(on_edit_cut), b);
	g_signal_connect(G_OBJECT(copy_item), "activate", G_CALLBACK(on_edit_copy), b);
	g_signal_connect(G_OBJECT(paste_item), "activate", G_CALLBACK(on_edit_paste), b);
	g_signal_connect(G_OBJECT(delete_item), "activate", G_CALLBACK(on_edit_delete), b);
	g_signal_connect(G_OBJECT(find_item), "activate", G_CALLBACK(search_dialog), b);
	g_signal_connect(G_OBJECT(find_next_item), "activate", G_CALLBACK(find_next), b);
	g_signal_connect(G_OBJECT(zoom_in_item), "activate", G_CALLBACK(zoom_in), b);
	g_signal_connect(G_OBJECT(zoom_out_item), "activate", G_CALLBACK(zoom_out), b);
	g_signal_connect(G_OBJECT(zoom_reset_item), "activate", G_CALLBACK(zoom_reset), b);
	g_signal_connect(G_OBJECT(fullscreen_item), "activate", G_CALLBACK(fullscreen), b);
//	g_signal_connect(G_OBJECT(settings_item), "activate", G_CALLBACK(temp_func), b);
	g_signal_connect(G_OBJECT(inspector_item), "activate", G_CALLBACK(inspector_toggle), b);
	g_signal_connect(G_OBJECT(source_item), "activate", G_CALLBACK(view_source), b);
	g_signal_connect(G_OBJECT(about_item), "activate", G_CALLBACK(about_dialog), NULL);
	
	/* Associate menus with items in the menubar */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit_item), edit_menu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(view_item), view_menu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(tools_item), tools_menu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_item), help_menu);
	
	/* Add menus to menu_bar */
	gtk_menu_bar_append(GTK_MENU_BAR(menubar), file_item);
	gtk_menu_bar_append(GTK_MENU_BAR(menubar), edit_item);
	gtk_menu_bar_append(GTK_MENU_BAR(menubar), view_item);
	gtk_menu_bar_append(GTK_MENU_BAR(menubar), tools_item);
	gtk_menu_bar_append(GTK_MENU_BAR(menubar), help_item);
	
	/* Add accelgroup to window */
	gtk_window_add_accel_group(GTK_WINDOW(b->window), accel_group);
	
	/* Set up right-click context menu */
	g_signal_connect(GTK_OBJECT(menubar), "button-press-event", G_CALLBACK(context_menu_popup), b);
	
	/* Show widgets */
	gtk_widget_show(open_item);
	gtk_widget_show(print_item);
	gtk_widget_show(quit_item);
	gtk_widget_show(cut_item);
	gtk_widget_show(copy_item);
	gtk_widget_show(paste_item);
	gtk_widget_show(delete_item);
	gtk_widget_show(find_item);
	gtk_widget_show(find_next_item);
	gtk_widget_show(zoom_in_item);
	gtk_widget_show(zoom_out_item);
	gtk_widget_show(zoom_reset_item);
	gtk_widget_show(fullscreen_item);
	gtk_widget_show(settings_item);
	gtk_widget_show(inspector_item);
	gtk_widget_show(source_item);
	gtk_widget_show(about_item);
	
	gtk_widget_show(file_item);
	gtk_widget_show(edit_item);
	gtk_widget_show(view_item);
	gtk_widget_show(tools_item);
	gtk_widget_show(help_item);
		
	return(GtkWidget*)menubar;
}

GtkWidget *
create_engine_menu(Browser *b)
{
	GtkWidget *menu;
	GtkWidget *item;
	SearchEngine *current;
	
	menu = gtk_menu_new();
		
	current = engine_list;
	while(current) {
		item = gtk_menu_item_new_with_label(current->name);
		gtk_menu_append(GTK_MENU(menu), item);
		g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(set_search_engine), b);
		gtk_widget_show(GTK_WIDGET(item));
		
		current = current->next;
	}
	
	return(GtkWidget*)menu;
}
