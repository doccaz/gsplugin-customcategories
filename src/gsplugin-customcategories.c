/*
 * Copyright (C) 2016 Richard Hughes
 */

#include <gsplugin-customcategories.h>

static const GsDesktopMap map_bb[] = {
    {"all", "Menu of BB All", {"X-Aplicativos", NULL}},
    {"arq30", "Menu of BB Arq 3.0", {"X-Aplicativos::X-Arq30", NULL}},
    {NULL}};
/* main categories */
/* Please keep category name and subcategory context synchronized!!! */
static const GsDesktopData msdata[] = {
    /* TRANSLATORS: this is the menu spec main category for Audio & Video */
    {"bb", map_bb, "Banco do Brasil",
     "virtualbox", "#215d9c", 100},
    {NULL}};

const GsDesktopData *
gs_desktop_get_data(void)
{
  return msdata;
}

void gs_plugin_initialize(GsPlugin *plugin)
{
  gs_plugin_add_rule(plugin, GS_PLUGIN_RULE_RUN_BEFORE, "appstream");
  fprintf(stdout, "[customcategories] Initializing plug-in\n");
}


gboolean
gs_plugin_add_categories(GsPlugin *plugin,
                         GPtrArray *list,
                         GCancellable *cancellable,
                         GError **error)
{
  fprintf(stdout, "[customcategories] There are %d categories\n", list->len);
  g_ptr_array_foreach(list, print_element, NULL);

  GdkRGBA key_color;
  GsCategory *category;

  /* add parent category */
  category = gs_category_new("bb");
  gs_category_set_icon(category, "virtualbox");
  gs_category_set_name(category, "Banco do Brasil");
  gs_category_add_desktop_group(category, "Blah");
  gs_category_set_score(category, 100);
  if (gdk_rgba_parse(&key_color, "#FFAA00"))
    gs_category_add_key_color(category, &key_color);

  /* add subcategories */
  g_autoptr(GsCategory) sub = gs_category_new("arq30");
  gs_category_add_desktop_group(sub, "X-SuSE-YaST");
  gs_category_set_name(sub, "Categoria da Biba");
  gs_category_add_child(category, sub);

  g_autoptr(GsCategory) sub2 = gs_category_new("biba");
  gs_category_add_desktop_group(sub2, "Spreadsheet");
  gs_category_set_name(sub2, "Categoria Biba Master");
  gs_category_add_child(category, sub2);
  g_ptr_array_add(list, category);
  fprintf(stdout, "[customcategories] Now there are %d categories\n", list->len);
  g_ptr_array_foreach(list, print_element, NULL);
  return TRUE;
}

gboolean
gs_plugin_add_category_apps(GsPlugin *plugin,
                            GsCategory *category,
                            GsAppList *list,
                            GCancellable *cancellable,
                            GError **error)
{

  fprintf(stdout, "[customcategories] adding apps to category %s\n", gs_category_get_id(category));

  fprintf(stdout, "[customcategories] There are %d apps\n", gs_app_list_length(list));
  g_autoptr(GsApp) app = gs_app_new("testebiba.desktop");
  gs_app_add_quirk(app, AS_APP_QUIRK_MATCH_ANY_PREFIX);
  gs_app_add_category(app, "bb");
  gs_app_add_category(app, "X-SuSE-YaST");
  gs_app_set_name(app, GS_APP_QUALITY_NORMAL, "Biba App");
  gs_app_list_add(list, app);
  for (int i = 0; i < gs_app_list_length(list); i++)
  {
    g_autoptr(GsApp) apptmp = gs_app_list_index(list, i);

    printf("[customcategories] app name = %s\n", gs_app_get_name(apptmp));
    g_autoptr(GPtrArray) cats = gs_app_get_categories(apptmp);
    for (int j = 0; j < cats->len; j++)
    {
      printf("[customcategories] %s\n", g_ptr_array_index(cats, j));
    }
  }

  fprintf(stdout, "[customcategories] Now there are %d apps\n", gs_app_list_length(list));
  //g_ptr_array_foreach(list, print_element, NULL);
  return TRUE;
}


void gs_plugin_adopt_app(GsPlugin *plugin, GsApp *app)
{
  if (app != NULL && gs_app_get_kind (app) == AS_APP_KIND_DESKTOP)
  {
    GPtrArray *cats = gs_app_get_categories(app);
    const gchar *catname;
    
  
    for (int i=0; i < cats->len; i++) 
    {
      printf("[customcategories] processing app %s (%d categories)\n", gs_app_get_name(app), cats->len);

                g_autofree const gchar *tmp = NULL;
                printf("1\n");
                GsCategory  *cat = cats->pdata[i];
                printf("2\n");
                tmp = gs_category_get_name(cat);
                printf("3\n");
           
      printf("[customcategories] category name = %s\n", catname);
      if (g_strcmp0("X-SuSE-YaST", catname) == 0)
      {
        printf("[customcategories] adopting app %s\n", gs_app_get_name(app));
       // gs_app_set_management_plugin(app, gs_plugin_get_name(plugin));
      }
      else
      {
        printf("[customcategories] skipping app %s\n", gs_app_get_name(app));
      }
    }
  }
}

void print_element(gpointer data, gpointer user_data)
{
  printf("[customcategories] %s - %s\n", gs_category_get_id(data), gs_category_get_name(data));
}