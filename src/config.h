#ifndef _CONFIG_H
#define _CONFIG_H

Conf *conf_copy(Conf *conf);
void conf_create_file(gchar *pathname);
void conf_init(Conf *conf);
void conf_load_from_file(Conf *conf);
Conf *conf_new();
void conf_save_to_file(Conf *conf);

#endif /* _CONFIG_H */
