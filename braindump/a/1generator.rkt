;; Ovaj modul je srž implementacije - analogan je, tipa, kodu koji informacije
;; kakve žive u giru pretvara u racket kod.
;;
#lang racket

;; meta 0
(require ffi/unsafe)

;; na nivou na kojem je i u ovom modulu -- meta 1
(provide funs/str->int)

;; meta 1
(begin-for-syntax

  (define (map-syntax lexenv f syn)
    (datum->syntax lexenv (map f (syntax->datum syn))))

  (define (funs/str->int/f syn)
    (syntax-case syn ()
      [(_ name ...)
       (with-syntax ([(external-name ...)
                      (map-syntax #f symbol->string #'(name ...))])
         
         ;; meta 0
         #'(begin
             (define libc (ffi-lib "libc" "6"))
             (define name (get-ffi-obj 'external-name libc (_fun _string -> _int)))
             ...))]))
  )

;; meta 1
(define-syntax funs/str->int funs/str->int/f)

