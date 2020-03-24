#include <gnome-software.h>
#include <glib.h>



void print_element(gpointer data, gpointer user_data);

#include <glib-object.h>

G_BEGIN_DECLS

typedef struct {
        const gchar     *id;
        const gchar     *name;
        const gchar     *fdo_cats[16];
} GsDesktopMap;

typedef struct {
        const gchar     *id;
        const GsDesktopMap *mapping;
        const gchar     *name;
        const gchar     *icon;
        const gchar     *key_colors;
        gint             score;
} GsDesktopData;

const GsDesktopData     *gs_desktop_get_data            (void);

struct _GsCategory
{       
        GObject          parent_instance;
        
        gchar           *id;
        gchar           *name;
        gchar           *icon;
        gint             score;
        GPtrArray       *key_colors;
        GPtrArray       *desktop_groups;
        GsCategory      *parent;
        guint            size;
        GPtrArray       *children;
};

G_END_DECLS

