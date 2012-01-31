;; Isto kao i prije, with a twist - ovaj modul prekapa po stvarima. Nema
;; potrebe da se njemu i nama zagorča život time da mu se sav koristan posao
;; definira u meta 1.
;;
#lang racket

;; require za meta -1
(require (for-template racket/base
                       ffi/unsafe))
;; racket/base???
;; -- Naravno. `#lang racket' importa racket, level-za-level, dakle ništa za
;; -1. makni `racket/base' i promatraj kako se klijent ovog modula raspada jer
;; ne vidi `#%app'! racket/base efektivno importa *osnovni scheme* u lex. env.
;; templejta.

;; Meta? Nema tu meta.
(provide funs/str->int/f)

(define (map-syntax lexenv f syn)
  (datum->syntax lexenv (map f (syntax->datum syn))))

(define (funs/str->int/f syn)
  (with-syntax ([(_ name ...) syn]
                [(_ external-name ...)
                 (map-syntax #f symbol->string syn)])

    ;; meta -1 !
    #'(begin
        (define libc (ffi-lib "libc" "6"))
        (define name (get-ffi-obj 'external-name libc (_fun _string -> _int)))
        ...)
    ))

