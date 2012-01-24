#include <string.h>
#include "lg-button.h"

static int lg_button_to_string(LgComponent *self, gchar *out) {
  static const char *text = "BUTTON";
  if(!LG_IS_BUTTON(self)) return -1;
  int len = strlen(text);
  if(out) strcpy(out, text);
  return len;
}

static void lg_button_init(LgButton *self) {
  self->label = NULL;
}

G_DEFINE_TYPE(LgButton, lg_button, LG_TYPE_COMPONENT);

static void lg_button_dispose(GObject *gobject) {
  G_OBJECT_CLASS(lg_button_parent_class)->dispose(gobject);
}

static void lg_button_finalize(GObject *gobject) {
  puts("ciao button");
  G_OBJECT_CLASS(lg_button_parent_class)->finalize(gobject);
}

void lg_button_set_property(GObject *object, guint id,
			 const GValue *value, GParamSpec *pspec) {
  LgButton *self = LG_BUTTON(object);
  if(id == PROP_BUTT_LABEL) {
    if(self->label) g_free((gpointer)self->label);
    const gchar* gstr = g_value_get_string(value);
    self->label = g_malloc(strlen(gstr) + 1);
    strcpy(self->label, gstr);
  } else {
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, id, pspec);
  }
}

void lg_button_get_property(GObject *object, guint id,
			    GValue *value, GParamSpec *pspec) {
  LgButton *self = LG_BUTTON(object);
  if(id == PROP_BUTT_LABEL)
    g_value_set_string(value, self->label);
  else
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, id, pspec);
}

static void lg_button_class_init(LgButtonClass *klass) {
  GObjectClass *gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->dispose = lg_button_dispose;
  gobject_class->finalize = lg_button_finalize;

  klass->parent_class.to_string = lg_button_to_string;

  gobject_class->set_property = lg_button_set_property;
  gobject_class->get_property = lg_button_get_property;

  GParamSpec *pspec =
    g_param_spec_string("label",
			" ... label",
			"Button's label",
			"",
			G_PARAM_READWRITE/*|G_PARAM_CONSTRUCT_ONLY*/);

  g_object_class_install_property(gobject_class,
                                  PROP_BUTT_LABEL,
				  pspec);

}

LgButton *lg_button_new() {
  puts("button construct");
  LgButton *foo = g_object_new(LG_TYPE_BUTTON, NULL);
  return foo;
}
