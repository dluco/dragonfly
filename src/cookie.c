#include "dragonfly.h"

#include <sys/file.h>

#define COOKIEJAR_TYPE         (cookiejar_get_type())
#define COOKIEJAR(obj)         (G_TYPE_CHECK_INSTANCE_CAST((obj), COOKIEJAR_TYPE, CookieJar))

typedef struct {
	SoupCookieJarText parent_instance;
	int lock;
} CookieJar;

typedef struct {
	SoupCookieJarTextClass parent_class;
} CookieJarClass;

G_DEFINE_TYPE(CookieJar, cookiejar, SOUP_TYPE_COOKIE_JAR_TEXT)

time_t sessiontime   = 3600;

void cookiejar_changed(SoupCookieJar *self, SoupCookie *old_cookie, SoupCookie *new_cookie)
{
	flock(COOKIEJAR(self)->lock, LOCK_EX);
	if (new_cookie && !new_cookie->expires && sessiontime) {
		soup_cookie_set_expires(new_cookie,
				soup_date_new_from_now(sessiontime));
	}
	SOUP_COOKIE_JAR_CLASS(cookiejar_parent_class)->changed(self,
			old_cookie, new_cookie);
	flock(COOKIEJAR(self)->lock, LOCK_UN);
}

static void cookiejar_class_init(CookieJarClass *klass)
{
	SOUP_COOKIE_JAR_CLASS(klass)->changed = cookiejar_changed;
	G_OBJECT_CLASS(klass)->get_property =
		G_OBJECT_CLASS(cookiejar_parent_class)->get_property;
	G_OBJECT_CLASS(klass)->set_property = cookiejar_set_property;
	G_OBJECT_CLASS(klass)->finalize = cookiejar_finalize;
	g_object_class_override_property(G_OBJECT_CLASS(klass), 1, "filename");
}

void cookiejar_finalize(GObject *self)
{
	close(COOKIEJAR(self)->lock);
	G_OBJECT_CLASS(cookiejar_parent_class)->finalize(self);
}

static void cookiejar_init(CookieJar *self)
{
	self->lock = open(cookiefile, 0);
}

SoupCookieJar *cookiejar_new(const char *filename, gboolean read_only)
{
	return g_object_new(COOKIEJAR_TYPE,
	                    SOUP_COOKIE_JAR_TEXT_FILENAME, filename,
	                    SOUP_COOKIE_JAR_READ_ONLY, read_only, NULL);
}

void cookiejar_set_property(GObject *self, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	flock(COOKIEJAR(self)->lock, LOCK_SH);
	G_OBJECT_CLASS(cookiejar_parent_class)->set_property(self, prop_id,
			value, pspec);
	flock(COOKIEJAR(self)->lock, LOCK_UN);
}
