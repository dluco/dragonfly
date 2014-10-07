#ifndef _SEARCH_ENGINE_H
#define _SEARCH_ENGINE_H

typedef struct _searchEngine {
	char *name;
	char *text;
	char *url;
	struct _searchEngine *next;
} SearchEngine;

SearchEngine *search_engine_list_find(const char *engine_name);

#endif /* _SEARCH_ENGINE_H */
