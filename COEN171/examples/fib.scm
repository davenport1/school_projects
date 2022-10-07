; vi:ai:lisp:sm
;
; fibonacci defined three different ways:
;   1) using a nested if
;   2) using a cond
;   3) using a logical or

(define (fib1 n)
  (if (= n 0) 1
    (if (= n 1) 1 (+ (fib1 (- n 1)) (fib1 (- n 2))))))

(define (fib2 n)
  (cond
    ((= n 0) 1)
    ((= n 1) 1)
    (else (+ (fib2 (- n 1)) (fib2 (- n 2))))))

(define (fib3 n)
  (if (or (= n 0) (= n 1)) 1 (+ (fib3 (- n 1)) (fib3 (- n 2)))))
