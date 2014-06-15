#include "dragonfly.h"
#include <string.h>

Conf *
conf_copy(Conf *conf)
{
	Conf *temp;
	
	temp = (Conf*)malloc(sizeof(Conf));
	if (!temp) {
		fprintf(stderr, "%s: Failed to allocate memory\n", PACKAGE);
	}
	
	temp->useragent = g_strdup(conf->useragent);
	//strncpy(temp->useragent, conf->useragent, strlen(conf->useragent));
	temp->homepage = g_strdup(conf->homepage);
	//strncpy(temp->homepage, conf->homepage, strlen(conf->homepage));
	temp->engine = g_strdup(conf->engine);
	//strncpy(temp->engine, conf->engine, strlen(conf->engine));
	temp->downloaddir = g_strdup(conf->downloaddir);
	//strncpy(temp->downloaddir, conf->downloaddir, strlen(conf->downloaddir));
	temp->enableplugins = conf->enableplugins;
	temp->enablescripts = conf->enablescripts;
	temp->enablefileaccess = conf->enablefileaccess;
	temp->strictssl = conf->strictssl;
	temp->enableinspector = conf->enableinspector;
	temp->loadimages = conf->loadimages;
	temp->enablespatialbrowsing = conf->enablespatialbrowsing;
	temp->enablespellchecking = conf->enablespellchecking;
	temp->hidebackground = conf->hidebackground;
	temp->fullcontentzoom = conf->fullcontentzoom;
	
	return temp;
}
