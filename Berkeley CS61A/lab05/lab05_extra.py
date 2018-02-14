from lab05 import *

## Extra Questions ##

# Q6
def filter(pred, lst):
    """Filters lst with pred using mutation.
    >>> original_list = [5, -1, 2, 0]
    >>> filter(lambda x: x % 2 == 0, original_list)
    >>> original_list
    [2, 0]
    """
    "*** YOUR CODE HERE ***"
    i = len(lst)-1
    while i >= 0:
        if not pred(lst[i]):
            lst.pop(i)
        i -= 1

# Q7
def reverse(lst):
    """Reverses lst using mutation.

    >>> original_list = [5, -1, 29, 0]
    >>> reverse(original_list)
    >>> original_list
    [0, 29, -1, 5]
    >>> odd_list = [42, 72, -8]
    >>> reverse(odd_list)
    >>> odd_list
    [-8, 72, 42]
    """
    "*** YOUR CODE HERE ***"
    if len(lst) > 1:
        tmp = lst.pop()
        reverse(lst)
        lst.insert(0, tmp)

# Q8
def counter(message):
    """ Returns a dictionary of each word in message mapped
    to the number of times it appears in the input string.

    >>> x = counter('to be or not to be')
    >>> x['to']
    2
    >>> x['be']
    2
    >>> x['not']
    1
    >>> y = counter('run forrest run')
    >>> y['run']
    2
    >>> y['forrest']
    1
    """
    word_list = message.split() # .split() returns a list of the words in the string. Try printing it!
    "*** YOUR CODE HERE ***"
    x = dict()
    for word in word_list:
        if word not in x:
            x[word] = 1
        else:
            x[word] += 1
    return x

# Q9
def make_fib():
    """Returns a function that returns the next Fibonacci number
    every time it is called.

    >>> fib = make_fib()
    >>> fib()
    0
    >>> fib()
    1
    >>> fib()
    1
    >>> fib()
    2
    >>> fib()
    3
    >>> fib2 = make_fib()
    >>> fib() + sum([fib2() for _ in range(5)])
    12
    """
    "*** YOUR CODE HERE ***"
    cur = 0
    nxt = 1
    def helper():
        nonlocal cur, nxt
        thiscur = cur
        tmp = nxt
        nxt += cur
        cur = tmp
        return thiscur
    return helper