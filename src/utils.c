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

void
load_engines(void)
{
	GKeyFile *key_file;
	gchar *path, **group_list;
	gsize num_groups;
	SearchEngine *current, *rear;
	int i;
	
	path = g_build_filename(g_get_user_config_dir(), "dragonfly", "engines", NULL);
	if (!g_file_test(path, G_FILE_TEST_EXISTS)) {
		/* engine file does not exist */
		fprintf(stderr, "%s: cannot load search engine file - %s\n", "dragonfly", path);
		return;
	}
	
	key_file = g_key_file_new();
	g_key_file_load_from_file(key_file, path, G_KEY_FILE_KEEP_COMMENTS, NULL);
	g_free(path);
	group_list = g_key_file_get_groups(key_file, &num_groups);
	
	rear = engine_list;
	for (i = 0; i < num_groups; i++) {
		if (!(current = (SearchEngine*)malloc(sizeof(SearchEngine)))) {
			fprintf(stderr, "%s: Failed to allocate memory\n", "dragonfly");
		}
		if (i == 0) {
			engine_list = current;
			rear = current;
		} else {
			rear->next = current;
			rear = current;
		}
		current->name = g_key_file_get_string (key_file, group_list[i], "name", NULL);
		current->text = g_key_file_get_string (key_file, group_list[i], "text", NULL);
		current->url = g_key_file_get_string (key_file, group_list[i], "uri", NULL);
		current->next = NULL;
	}
	
	g_strfreev (group_list);
	g_key_file_free (key_file);
	
	return;
}
