#ifndef _BROWSER_H
#define _BROWSER_H

SearchEngine *browser_get_default_search_engine (Browser *b);
void browser_set_default_search_engine (Browser *b, SearchEngine *engine);
void browser_set_settings (Browser *b);
Browser *browser_new (void);

#endif /* _BROWSER_H */
