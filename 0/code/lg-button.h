#ifndef _LG_BUTTON_
#define _LG_BUTTON_

#include <glib-object.h>
#include <glib.h>

#include "lg-component.h"

#define LG_TYPE_BUTTON (lg_button_get_type ())

#define LG_BUTTON(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), LG_TYPE_BUTTON, LgButton))

#define LG_IS_BUTTON(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), LG_TYPE_BUTTON))

#define LG_BUTTON_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), LG_TYPE_BUTTON, LgButtonClass))

#define LG_IS_BUTTON_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), LG_TYPE_BUTTON))

#define LG_BUTTON_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS((obj), LG_TYPE_BUTTON, LgButtonClass))

enum {
  PROP_BUTT_LABEL = PROP_COMP_LAST,

  PROP_BUTT_LAST
};

typedef struct {
  LgComponentClass parent_class;
  void (*click)(void);
} LgButtonClass;

typedef struct {
  LgComponent parent;
  gchar* label;
  //action listener iface
} LgButton;

GType lg_button_get_type(void);
//void lg_button_set_property(GObject*, guint, const GValue*, GParamSpec*);
//void lg_button_get_property(GObject*, guint, GValue*, GParamSpec*);

LgButton *lg_button_new();

#endif //_LG_BUTTON_
