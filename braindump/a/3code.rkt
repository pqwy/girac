;; This little piggie is the client code.
;;
#lang racket

;; meta 0. no meta at all.
(require "2provider.rkt")

(for ([s '("34" "23kk" "klj"
           "floccinaucinihilipilificate"
           "prijestolonasljednikovica")])
  (printf "[~s : ~s] ~s~n" s (strlen s) (atoi s)))
