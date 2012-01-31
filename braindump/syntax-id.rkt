;; makroi višeg reda, higijeničnost identifikatora koje sintetiziraju i
;; zanimljivo ponašanje syntax-id-rules forme -- makro ne samo kao specijalna
;; forma, nego i specijalni *atom*.

#lang racket

(provide define/indirect define/screaming-binding)

(struct box1 [(b #:mutable)])

(define-syntax-rule (define/indirect name value)
  (begin
    (define anonymous-box (box1 value))
    (define-syntax name
      (syntax-id-rules (set!)
        [(set! name v) (set-box1-b! anonymous-box v)]
        [(name e (... ...)) ((box1-b anonymous-box) e (... ...))]
        [name (box1-b anonymous-box)]))))

(define-syntax-rule (define/screaming-binding name value)
  (begin
    (define anonymous-var value)
    (define (noise) (printf "[~s] SCREAM!~n" 'name) anonymous-var)
    (define-syntax name
      (syntax-id-rules (set!)
        [(set! name v) (set! anonymous-var v)]
        [(name e (... ...)) ((noise) e (... ...))]
        [name (noise)]))))

