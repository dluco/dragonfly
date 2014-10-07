#ifndef _DIALOG_H
#define _DIALOG_H

void run_dialog_message(GtkWidget *window, GtkMessageType type, gchar *message, ...);
const gchar *save_dialog(const gchar *filename, char *directory, Browser *b);
void about_dialog(void);

#endif /* _DIALOG_H */
