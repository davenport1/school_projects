; vi:ai:lisp:sm

; filter written using a let to extract the head and tail of the list

(define (filter f lst)
  (if (null? lst) lst
    (let
      ((x (car lst))
       (xs (cdr lst)))
      (if (f x) (cons x (filter f xs)) (filter f xs)))))


; filter written without using a let
; note that in this case cond works better than an if

(define (filter f lst)
  (cond
    ((null? lst) lst)
    ((f (car lst)) (cons (car lst) (filter f (cdr lst))))
    (else (filter f (cdr lst)))))
