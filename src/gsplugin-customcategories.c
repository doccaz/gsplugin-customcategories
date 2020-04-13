/*
 * Copyright (C) 2016 Richard Hughes
 */

#include <gsplugin-customcategories.h>

static const GsDesktopMap map_bb[] = {
    {"bb-apps", "Aplicativos BB", {"X-Aplicativos", NULL}},
    {"bb-arq30", "Enxoval Arq 3.0", {"X-Arq30", NULL}},
    {"bb-mobile", "Testes Mobile", {"X-Mobile", NULL}},
    {"bb-plataforma", "Plataforma 3.0", {"X-Plataforma", NULL}},
    {"bb-grafeno", "Grafeno", {"X-Grafeno", NULL}},
    {NULL}};
/* main categories */
/* Please keep category name and subcategory context synchronized!!! */
static const GsDesktopData msdata[] = {
    {"bancodobrasil", map_bb, "Banco do Brasil",
     "bb", "#fee50c", 100},
    {NULL}};

const GsDesktopData *
_gs_desktop_get_data(void)
{
  return msdata;
}

void gs_plugin_initialize(GsPlugin *plugin)
{
  gs_plugin_add_rule(plugin, GS_PLUGIN_RULE_RUN_BEFORE, "appstream");
  gs_plugin_add_rule (plugin, GS_PLUGIN_RULE_CONFLICTS, "fwupd");
//   gs_plugin_add_rule (plugin, GS_PLUGIN_RULE_CONFLICTS, "packagekit-refine");
  gs_plugin_add_rule (plugin, GS_PLUGIN_RULE_CONFLICTS, "shell-extensions");

  fprintf(stdout, "[customcategories] Initializing plug-in\n");
}


gboolean
gs_plugin_add_categories (GsPlugin *plugin,
                          GPtrArray *list,
                          GCancellable *cancellable,
                          GError **error)
{
        const GsDesktopData *msdata;
        guint i, j, k;

        msdata = _gs_desktop_get_data ();
        for (i = 0; msdata[i].id != NULL; i++) {
                GdkRGBA key_color;
                GsCategory *category;

                /* add parent category */
                category = gs_category_new (msdata[i].id);
                gs_category_set_icon (category, msdata[i].icon);
                gs_category_set_name (category, msdata[i].name);
                gs_category_set_score (category, msdata[i].score);
                if (gdk_rgba_parse (&key_color, msdata[i].key_colors))
                        gs_category_add_key_color (category, &key_color);
                g_ptr_array_add (list, category);

                /* add subcategories */
                for (j = 0; msdata[i].mapping[j].id != NULL; j++) {
                        const GsDesktopMap *map = &msdata[i].mapping[j];
                        g_autoptr(GsCategory) sub = gs_category_new (map->id);
                        for (k = 0; map->fdo_cats[k] != NULL; k++)
                                gs_category_add_desktop_group (sub, map->fdo_cats[k]);
                        gs_category_set_name (sub, map->name);
                        gs_category_add_child (category, sub);
                }
        }
        return TRUE;
}


// void gs_plugin_adopt_app (GsPlugin *plugin, GsApp *app)
// {
//         const GsDesktopData *msdata;
//         guint i, j, k;
//         msdata = _gs_desktop_get_data ();
//         for (i = 0; msdata[i].id != NULL; i++) {
//                 for (j = 0; msdata[i].mapping[j].id != NULL; j++) {
//                         const GsDesktopMap *map = &msdata[i].mapping[j];
//                         //printf("[customcategories] adopt app working on %s\n", gs_app_get_name(app));                                
//                         for (k = 0; map->fdo_cats[k] != NULL; k++) {
//                                 if (gs_app_has_category(app, map->fdo_cats[k])) {
//                                     printf("[customcategories] adopting app %s (has category %s)\n", gs_app_get_name(app), map->fdo_cats[k]);
//                                     printf("[customcategories] app details: %s\n", gs_app_to_string(app));
//                                     // gs_app_set_management_plugin (app, gs_plugin_get_name (plugin));
//                                 }
//                         }

//                 }
//         }
// }


// gboolean
// gs_plugin_add_category_apps (GsPlugin *plugin,
//                              GsCategory *category,
//                              GsAppList *list,
//                              GCancellable *cancellable,
//                              GError **error)
// {
//         GPtrArray *desktop_groups;
//         GsCategory *parent;
//         const GsDesktopData *msdata;
//         guint i, j, k;

//         /* already set */
//         desktop_groups = gs_category_get_desktop_groups (category);
//         printf("[customcategories] add apps to category -> %s (%s) -> total %d apps\n", gs_category_get_id(category), gs_category_get_name(category), gs_app_list_length(list));

//         /* not valid */
//         parent = gs_category_get_parent (category);
//         if (parent == NULL)
//                 return TRUE;

//         /* find desktop_groups for a parent::child category */
//         msdata = _gs_desktop_get_data ();
//         for (i = 0; msdata[i].id != NULL; i++) {

//                 if (g_strcmp0 (gs_category_get_id (parent), msdata[i].id) != 0)
//                         continue;
//                 for (j = 0; msdata[i].mapping[j].id != NULL; j++) {
//                         const GsDesktopMap *map = &msdata[i].mapping[j];
//                         if (g_strcmp0 (gs_category_get_id (category), map->id) != 0)
//                                 continue;
//                         printf("[customcategories] working on %s->%s\n", gs_category_get_id(category), map->id);                                
//                         for (k = 0; map->fdo_cats[k] != NULL; k++) {
//                                 gs_category_add_desktop_group (category, map->fdo_cats[k]);
//                                 printf("[customcategories] adding group -> %s\n", map->fdo_cats[k]);
//                                 printf("[customcategories] start add apps to category %s\n", gs_category_get_id(category));
//                                 g_autoptr(GsApp) app = gs_app_new ("org.kde.k3b.desktop");
//                                 gs_app_list_add (list, app);
//                                 printf("[customcategories] after add apps to category -> %s (%s) -> total %d apps\n", gs_category_get_id(category), gs_category_get_name(category), gs_app_list_length(list));
//                         }

//                 }
//         }
//         return TRUE;
// }

void print_element(gpointer data, gpointer user_data)
{
  printf("[customcategories] %s - %s\n", gs_category_get_id(data), gs_category_get_name(data));
}
