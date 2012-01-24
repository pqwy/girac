#include <stdio.h>
#include <glib-object.h>

#include <girepository.h>

#include "lg-component.h"
#include "lg-button.h"

int main(int argc, const char **argv) {
  if(argc >= 2) {
    g_irepository_dump(argv[1], NULL);
  }
  g_type_init();

  //new-delete
  g_object_unref(g_object_new(LG_TYPE_BUTTON, NULL));

  //
  GValue lbl = G_VALUE_INIT;
  g_value_init(&lbl, G_TYPE_STRING);
  g_value_set_static_string(&lbl, "Foo");

  //LgComponent* btn = lg_button_new();
  LgComponent* btn = g_object_new(LG_TYPE_BUTTON, NULL);
  g_object_set_property(G_OBJECT(btn), "label", &lbl);

  gchar buff[1024] = {0};
  if(lg_component_to_string(btn, buff) != -1)
    puts(buff);

  {
    GValue val = G_VALUE_INIT;
    g_value_init(&val, G_TYPE_STRING);
    g_object_get_property(G_OBJECT(btn), "label", &val);
    printf("label: %s\n", g_value_get_string(&val));
    g_value_reset(&val);
  }

  {
    GValue val = G_VALUE_INIT;
    g_value_init(&val, G_TYPE_INT);
    g_object_get_property(G_OBJECT(btn), "HWND", &val);
    printf("hwnd: %d\n", g_value_get_int(&val));
  }
  
  g_object_unref(btn);

  return 0;
}
