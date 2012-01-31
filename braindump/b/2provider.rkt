#lang racket

;; forall n. meta n -> meta n+1
(require (for-syntax "1generator.rkt"))

(provide atoi strlen)

;; meta 1 - naš meta 1 djeluje na importani meta 1
(define-syntax funs/str->int funs/str->int/f)

;; kao i obično, meta 1 poziv stvara meta 0 kod.
(funs/str->int atoi strlen)

