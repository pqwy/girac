#include <limits.h>
#include "lg-component.h"

/**
 * tut_triangle_get_color:
 * @triangle: a #TutTriangle
 * @color: return location for a #ClutterColor
 *
 * Retrieves the color of @triangle.
 */

static int hwnd_counter() {
  static int cnt;
  return cnt++;
}

int lg_component_to_string(LgComponent *self, gchar *out) {
  if(!LG_IS_COMPONENT(self)) return -1;
  return LG_COMPONENT_GET_CLASS(self)->to_string(self, out);
}

static void lg_component_init(LgComponent *self) {
  self->hwnd = hwnd_counter();
}

G_DEFINE_ABSTRACT_TYPE(LgComponent, lg_component, G_TYPE_OBJECT);

static void lg_component_dispose(GObject *gobject) {
  //  LgComponent *cmp = LG_COMPONENT(gobject);
  //  LgComponentClass *klass = LG_COMPONENT_GET_CLASS(cmp);
  //  G_OBJECT_CLASS(&klass->parent_class)->dispose(gobject);
  G_OBJECT_CLASS(lg_component_parent_class)->dispose(gobject);
}

static void lg_component_finalize(GObject *gobject) {
  G_OBJECT_CLASS(lg_component_parent_class)->finalize(gobject);
}

void lg_component_get_property(GObject *object, guint id,
			       GValue *value, GParamSpec *pspec) {
  LgComponent *self = LG_COMPONENT(object);
  if(id == PROP_COMP_HWND)
    g_value_set_int(value, self->hwnd);
  else
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, id, pspec);
}

static void lg_component_class_init(LgComponentClass *klass) {
  GObjectClass *gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->dispose = lg_component_dispose;
  gobject_class->finalize = lg_component_finalize;

  klass->to_string = NULL;

  //  gobject_class->set_property = lg_component_set_property;
  gobject_class->get_property = lg_component_get_property;

  GParamSpec *pspec = g_param_spec_int("HWND",
				       "hwnd",
				       "Component's HWND",
				       0, INT_MAX, 0,
				       G_PARAM_READABLE);

  g_object_class_install_property(gobject_class,
                                  PROP_COMP_HWND,
				  pspec);
}
