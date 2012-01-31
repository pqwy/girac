;; Ovaj modul je klijent jezgri, ali biblioteka pravom klijenskom kodu. Recimo,
;; on čita neki .gir. Idealno, niti ne postoji kao fajl.
;;
#lang racket

;; forall n. meta n -> meta n
(require "1generator.rkt")

;; meta 0
(provide atoi strlen)

;; meta 1, stvara meta 0 koji izvršava bind
(funs/str->int atoi strlen)

