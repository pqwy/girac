gcc main.c -o ldr `pkg-config --cflags gobject-introspection-1.0 gobject-2.0 glib-2.0 libffi` -Wall `pkg-config --libs gobject-introspection-1.0 gobject-2.0 glib-2.0 libffi` --std=c99 -ldl

