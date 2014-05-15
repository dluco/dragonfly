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

#include "browser.h"
#include "callback.h"

#endif /* _DRAGONFLY_H */
