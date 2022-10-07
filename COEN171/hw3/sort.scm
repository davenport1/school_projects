;Matthew Davenport
;COEN 171 HW 3 
;quicksort using scheme

(define (filter f lst)
    (cond 
        ((null? lst) lst)
        ((f (car lst)) (cons (car lst) (filter f (cdr lst))))
        (else (filter f (cdr lst)))))

(define (quicksort lst)
        (if(null? lst) lst
        (let*
            ((x (car lst))
             (y (cdr lst))
             (above (lambda (y) (>= y x)))
             (below (lambda (y) (< y x))))
        (append
            (quicksort (filter below y)) (cons x (quicksort (filter above y)))))))











































