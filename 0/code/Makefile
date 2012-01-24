CC = gcc
CFLAGS = `pkg-config --cflags gobject-introspection-1.0 gobject-2.0 glib-2.0` -Wall -g
LDFLAGS = `pkg-config --libs gobject-introspection-1.0 gobject-2.0 glib-2.0`

all: wdg so gir

wdg: main.o so
	gcc main.o -llg $(LDFLAGS) -o wdg -L.

main.o: main.c lg-component.h lg-button.h
	gcc -c $(CFLAGS) main.c -o main.o

so: liblg.so

liblg.so: lg-component.o lg-button.o
	gcc lg-component.o lg-button.o --shared $(LDFLAGS) -o liblg.so

lg-component.o: lg-component.c lg-component.h
	gcc lg-component.c -c $(CFLAGS) -fPIC -o lg-component.o

lg-button.o: lg-button.c lg-button.h lg-component.h
	gcc lg-button.c -c $(CFLAGS) -fPIC -o lg-button.o

run: wdg
	LD_LIBRARY_PATH=. ./wdg

gir: Lg.gir

Lg.gir: so
	LD_LIBRARY_PATH=. g-ir-scanner --include=GObject-2.0 --namespace=Lg --nsversion=1.0 --library=lg --pkg=gobject-2.0  --warn-all lg-component.c lg-component.h lg-button.c lg-button.h -o Lg-1.0.gir

clean:
	rm -rf *~ *.o liglg.so wdg Lg.gir
