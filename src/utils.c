#include "dragonfly.h"

#include <string.h>
#include <glib/gstdio.h>

char *
buildpath(const char *path) {
	char *apath, *p;
	FILE *f;

	/* creating directory */
	if(path[0] == '/') {
		apath = g_strdup(path);
	} else if(path[0] == '~') {
		if(path[1] == '/') {
			apath = g_strconcat(g_get_home_dir(), &path[1], NULL);
		} else {
			apath = g_strconcat(g_get_home_dir(), "/",
					&path[1], NULL);
		}
	} else {
		apath = g_strconcat(g_get_current_dir(), "/", path, NULL);
	}

	if((p = strrchr(apath, '/'))) {
		*p = '\0';
		g_mkdir_with_parents(apath, 0700);
		g_chmod(apath, 0700); /* in case it existed */
		*p = '/';
	}
	/* creating file (gives error when apath ends with "/") */
	if((f = fopen(apath, "a"))) {
		g_chmod(apath, 0600); /* always */
		fclose(f);
	}

	return apath;
}

SearchEngine *
load_engines (const gchar *enginefile)
{
	GKeyFile *key_file;
	gchar **group_list;
	gsize num_groups;
	int i;
	SearchEngine *engine_list, *current;
	
	key_file = g_key_file_new ();
	
	g_key_file_load_from_file (key_file, enginefile, G_KEY_FILE_KEEP_COMMENTS, NULL);
	
	group_list = g_key_file_get_groups (key_file, &num_groups);
	
	for (i = 0; i < num_groups; i++) {
		if (!(current = (SearchEngine*) malloc (sizeof (SearchEngine)))) {
			fprintf (stderr, "Error: Failed to allocate memory\n");
		}
		
		current->name = g_key_file_get_string (key_file, group_list[i], "name", NULL);
		current->text = g_key_file_get_string (key_file, group_list[i], "text", NULL);
		current->url = g_key_file_get_string (key_file, group_list[i], "uri", NULL);
		
		current->next = NULL;
		engine_list = current;
	}
	
	g_strfreev (group_list);
	g_key_file_free (key_file);
	
	return engine_list;
}
