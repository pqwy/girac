(require ffi/unsafe
         ffi/unsafe/define)

(define libglib (ffi-lib "/usr/lib/libgobject-2.0"))
(define liblg (ffi-lib "/home/aka/devel/snippets/c/gobj/lg/code/liblg"))

(define _gobject-pointer (_cpointer 'GObject))
(define g-type-init (get-ffi-obj "g_type_init" libglib (_fun -> _void)))

(define _g-object-unref (get-ffi-obj "g_object_unref" libglib (_fun _gobject-pointer -> _void)))
(define (g-object-unref obj)
  (_g-object-unref (cast obj _pointer _gobject-pointer)))

(define _button-pointer (_cpointer 'LgButton))
(define _button-new (get-ffi-obj "lg_button_new" liblg (_fun -> _button-pointer)))
(define (button-new)
  (let ((obj (_button-new)))
    (register-finalizer obj g-object-unref)
    obj))

(define _component-pointer (_cpointer 'LgComponent))
(define _component-to-string (get-ffi-obj "lg_component_to_string" liblg
                                          (_fun _component-pointer _pointer -> _int)))

(g-type-init)

(let* ((btn (button-new))
       (cmp (cast btn _pointer _component-pointer))
       (buff (malloc 'atomic (+ 1 (_component-to-string cmp #f)))))
  (_component-to-string cmp buff)
  (cast buff _pointer _string))

(collect-garbage)
