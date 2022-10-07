
;Matthew Davenport
;COEN 171 HW 3
;Binary search tree functions member and insert in scheme

(define (insert t x)
	(cond
		((null? t) (list x  '() '()))	;t is null, create new node 
		((< x (car t)) (list (car t) (insert (cadr t) x) (caddr t)))	;x less than current head
		((> x (car t)) (list (car t) (cadr t) (insert (caddr t) x)))	;x greater than current head
		(else t)))											

(define (member? t x)
	(cond
		((null? t) #f)									;reached end of tree without finding x
		((< x (car t)) (member? (cadr t) x))			;x < current head
		((> x (car t)) (member? (caddr t) x))			;x > current head
		(else #t)))										;x must = current head, return true

