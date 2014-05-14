#ifndef _DRAGONFLY_H
#define _DRAGONFLY_H

/*	#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif	*/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct Browser {
	GtkWidget *window;
	struct Browser *next;
} Browser;

static Browser *browsers = NULL; 

#include "callback.h"
#include "browser.h"
/*
#include "menu.h"
#include "about.h"
*/

#endif /* _DRAGONFLY_H */
