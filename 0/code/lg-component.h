#ifndef _LG_COMPONENT_
#define _LG_COMPONENT_

#include <glib-object.h>
#include <glib.h>

G_BEGIN_DECLS

#define LG_TYPE_COMPONENT (lg_component_get_type ())

#define LG_COMPONENT(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), LG_TYPE_COMPONENT, LgComponent))

#define LG_IS_COMPONENT(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), LG_TYPE_COMPONENT))

#define LG_COMPONENT_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), LG_TYPE_COMPONENT, LgComponentClass))

#define LG_IS_COMPONENT_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), LG_TYPE_COMPONENT))

#define LG_COMPONENT_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS((obj), LG_TYPE_COMPONENT, LgComponentClass))

enum {
  PROP_0,

  PROP_COMP_HWND,

  PROP_COMP_LAST
};

typedef struct {
  GObject parent;
  gint hwnd;
} LgComponent;

typedef struct {
  GObjectClass parent_class;
  int (*to_string)(LgComponent*, gchar*);
} LgComponentClass;

GType lg_component_get_type(void);
int lg_component_to_string(LgComponent*, gchar*);

//void lg_component_get_property(GObject*, guint, GValue*, GParamSpec*);

G_END_DECLS

#endif //_LG_COMPONENT_
