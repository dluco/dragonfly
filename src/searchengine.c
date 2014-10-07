#include <string.h>
#include "searchengine.h"

extern SearchEngine *engine_list;

SearchEngine *search_engine_list_find(const char *engine_name)
{
	SearchEngine *current = engine_list;
	while(current) {
		if (strncmp(engine_name, current->name, strlen(engine_name)) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}
