#ifndef _COOKIE_H
#define _COOKIE_H

void cookiejar_changed (SoupCookieJar *self, SoupCookie *old_cookie, SoupCookie *new_cookie);
void cookiejar_finalize (GObject *self);
SoupCookieJar *cookiejar_new (const char *filename, gboolean read_only);
void cookiejar_set_property (GObject *self, guint prop_id, const GValue *value, GParamSpec *pspec);

#endif /* _COOKIE_H */
