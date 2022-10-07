; vi:ai:lisp:sm
;
; append is built into Scheme, but we redefine it here to demonstrate
; how to use a let to keep track of the head and tail of the list

(define (append l1 l2)
  (cond
    ((null? l1) l2)
    (else
      (let
	((x (car l1))
	 (xs (cdr l1)))
	(cons x (append xs l2))))))
