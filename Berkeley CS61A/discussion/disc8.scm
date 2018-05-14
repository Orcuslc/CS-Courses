;;; 2.1.1
; a
; 1
; b
; 1
; c
; a

;;; 3.1.1
; 1
; 3
; 25
; a
; b
; 3

;;; 4.3.1
; 1
; 10
; -96
; 2

;;; 4.6.1
(define (factorial x)
	(cond ((< x 0) 0)
		  ((<= x 1) 1)
		  (else (* x (factorial (- x 1))))
	)
)

;;; 4.6.2
(define (fib n)
	(if (< n 2) 1
		(+ (fib (- n 1)) (fib (- n 2)))
	)
)

;;; 5.1
(define (concat a b)
	(if (null? a) 
		b
		(cons (car a) (concat (cdr a) b))
	)
)

;;; 5.2
(define (replicate x n)
	(if (= 0 n)
		'()
		(cons x (replicate x (- n 1)))
	)
)

;;; 5.3
(define (uncompress s)
	(if (null? s)
		'()
		(concat (replicate (car (car s)) (car (cdr (car s)))) (uncompress (cdr s)))
	)
)

;;; 5.4
(define (map fn lst)
	(if (null? lst)
		nil
		(cons (fn (car lst))
			  (map fn (cdr lst)))
	)
)

(define (deep-apply fn nested-lst)
	(if (null? nested-lst)
		'()
		(if (list? (car nested-lst))
			(cons (deep-apply fn (car nested-lst)) (deep-apply fn (cdr nested-lst)))
			(cons (fn (car nested-lst)) (deep-apply fn (cdr nested-lst)))
		)
	)
)

;;; 6.1
(define (make-tree root branches) (cons root branches))

(define (root tree)
	(car tree)
)

(define (branches tree)
	(cdr tree)
)

;;; 6.2
(define (tree-sum tree)
	(if (null? tree)
		0
		(+ (root tree) (map tree-sum (branches tree)))
	)
)

;;; 6.3
(define (path-product-tree t)
	(define (product tree val)
		(define (partial-product tree) (product tree (* (root tree) val)))
		(make-tree (* (root tree) val) (map partial-product (branches tree)))
	)
	(product tree 1)
)