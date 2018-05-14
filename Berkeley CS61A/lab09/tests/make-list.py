test = {
  'name': 'make-list',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          scm> (define a '(1))
          a
          scm> a
          (1)
          scm> (define b (cons 2 a))
          b
          scm> b
          (2 1)
          scm> (define c (list 3 b))
          c
          scm> c
          (3 (2 1))
          scm> (car c)
          3
          scm> (cdr c)
          ((2 1))
          scm> (car (car (cdr c)))
          2
          scm> (cdr (car (cdr c)))
          (1)
          """,
          'hidden': False,
          'locked': False
        },
        {
          'code': r"""
          scm> lst  ; type out exactly how Scheme would print the list
          ((1) 2 (3 . 4) 5)
          """,
          'hidden': False,
          'locked': False
        }
      ],
      'scored': True,
      'setup': r"""
      scm> (load 'lab09)
      scm> (load 'lab09_extra)
      """,
      'teardown': '',
      'type': 'scheme'
    },
    {
      'cases': [
        {
          'code': r"""
          scm> (define bees '(knees))
          bees
          scm> (cons 'cows (cons 3 bees))
          (cows 3 knees)
          scm> (cons 'cows (car bees))
          (cows . knees)
          scm> (car (cdr bees))  # Type SchemeError if you think this errors
          SchemeError
          scm> (define kfc '((chicks) . (picks . ticks)))
          kfc
          scm> kfc
          ((chicks) picks . ticks)
          scm> (define cfk (list (cdr kfc) (car bees)))
          cfk
          scm> cfk
          ((picks . ticks) knees)
          """,
          'hidden': False,
          'locked': False
        }
      ],
      'scored': True,
      'setup': r"""
      
      """,
      'teardown': '',
      'type': 'scheme'
    }
  ]
}
