#ifndef _DRAGONFLY_H
#define _DRAGONFLY_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <webkit/webkit.h>

extern Conf *main_conf;
extern Browser *browsers;
extern SearchEngine *engine_list;
extern char *cookiefile;

#include "about.h"
#include "callback.h"
#include "config.h"
#include "cookie.h"
#include "browser.h"
#include "dialog.h"
#include "download.h"
#include "menu.h"
#include "search.h"
#include "searchengine.h"
#include "toolbar.h"
#include "utils.h"

#define BUFSIZE 1024

#endif /* _DRAGONFLY_H */
