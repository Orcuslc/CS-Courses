def make_to_string(front, mid, back, empty_repr):
    """ Returns a function that turns linked lists to strings.

    >>> stans_to_string = make_to_string("[", "|-]-->", "", "[]")
    >>> michelles_to_string = make_to_string("(", " . ", ")", "()")
    >>> lst = Link(1, Link(2, Link(3, Link(4))))
    >>> stans_to_string(lst)
    '[1|-]-->[2|-]-->[3|-]-->[4|-]-->[]'
    >>> stans_to_string(Link.empty)
    '[]'
    >>> michelles_to_string(lst)
    '(1 . (2 . (3 . (4 . ()))))'
    >>> michelles_to_string(Link.empty)
    '()'
    """
    "*** YOUR CODE HERE ***"
    def make(lst):
        if lst is Link.empty:
            return empty_repr
        return front + str(lst.first)+ mid + make(lst.rest) + back
    return make
    

def mutate_reverse(link):
    """Mutates the Link so that its elements are reversed.

    >>> link = Link(1)
    >>> mutate_reverse(link)
    >>> link
    Link(1)

    >>> link = Link(1, Link(2, Link(3)))
    >>> mutate_reverse(link)
    >>> link
    Link(3, Link(2, Link(1)))
    """
    "*** YOUR CODE HERE ***"
    if link and link.rest:
        mutate_reverse(link.rest)
        while link.rest:
            link.first, link.rest.first = link.rest.first, link.first
            link = link.rest


def tree_map(fn, t):
    """Maps the function fn over the entries of tree and returns the
    result in a new tree.

    >>> numbers = Tree(1,
    ...                [Tree(2,
    ...                      [Tree(3),
    ...                       Tree(4)]),
    ...                 Tree(5,
    ...                      [Tree(6,
    ...                            [Tree(7)]),
    ...                       Tree(8)])])
    >>> print_tree(tree_map(lambda x: 2**x, numbers))
    2
      4
        8
        16
      32
        64
          128
        256
    """
    "*** YOUR CODE HERE ***"
    if t.is_leaf():
        return Tree(fn(t.label))
    return Tree(fn(t.label), [tree_map(fn, l) for l in t.branches])
    


def add_trees(t1, t2):
    """
    >>> numbers = Tree(1,
    ...                [Tree(2,
    ...                      [Tree(3),
    ...                       Tree(4)]),
    ...                 Tree(5,
    ...                      [Tree(6,
    ...                            [Tree(7)]),
    ...                       Tree(8)])])
    >>> print_tree(add_trees(numbers, numbers))
    2
      4
        6
        8
      10
        12
          14
        16
    >>> print_tree(add_trees(Tree(2), Tree(3, [Tree(4), Tree(5)])))
    5
      4
      5
    >>> print_tree(add_trees(Tree(2, [Tree(3)]), Tree(2, [Tree(3), Tree(4)])))
    4
      6
      4
    >>> print_tree(add_trees(Tree(2, [Tree(3, [Tree(4), Tree(5)])]), \
    Tree(2, [Tree(3, [Tree(4)]), Tree(5)])))
    4
      6
        8
        5
      5
    """
    "*** YOUR CODE HERE ***"
    if t1.is_leaf() and t2.is_leaf():
        return Tree(t1.label+t2.label)
    elif t1.is_leaf():
        return Tree(t1.label+t2.label, t2.branches)
    elif t2.is_leaf():
        return Tree(t1.label+t2.label, t1.branches)
    else:
        if len(t1.branches) == len(t2.branches):
            return Tree(t1.label+t2.label, [add_trees(i, j) for (i, j) in zip(t1.branches, t2.branches)])
        elif len(t1.branches) > len(t2.branches):
            return Tree(t1.label+t2.label, [add_trees(i, j) for (i, j) in zip(t1.branches, t2.branches)] + [t1.branches[i] for i in range(len(t2.branches), len(t1.branches))])
        else:
            return Tree(t1.label+t2.label, [add_trees(i, j) for (i, j) in zip(t1.branches, t2.branches)] + [t2.branches[i] for i in range(len(t1.branches), len(t2.branches))])

# Link
class Link:
    """A linked list.

    >>> s = Link(1, Link(2, Link(3)))
    >>> s.first
    1
    >>> s.rest
    Link(2, Link(3))
    """
    empty = ()

    def __init__(self, first, rest=empty):
        assert rest is Link.empty or isinstance(rest, Link)
        self.first = first
        self.rest = rest

    def __repr__(self):
        if self.rest is Link.empty:
            return 'Link({})'.format(self.first)
        else:
            return 'Link({}, {})'.format(self.first, repr(self.rest))
def print_link(link):
    """Print elements of a linked list link.

    >>> link = Link(1, Link(2, Link(3)))
    >>> print_link(link)
    <1 2 3>
    >>> link1 = Link(1, Link(Link(2), Link(3)))
    >>> print_link(link1)
    <1 <2> 3>
    >>> link1 = Link(3, Link(Link(4), Link(5, Link(6))))
    >>> print_link(link1)
    <3 <4> 5 6>
    """
    print('<' + helper(link).rstrip() + '>')

def helper(link):
    if link == Link.empty:
        return ''
    elif isinstance(link.first, Link):
        return '<' + helper(link.first).rstrip() + '> ' + helper(link.rest)
    else:
        return str(link.first) +' '+  helper(link.rest)

# Tree
class Tree:
    def __init__(self, label, branches=[]):
        for c in branches:
            assert isinstance(c, Tree)
        self.label = label
        self.branches = branches

    def __repr__(self):
        if self.branches:
            branches_str = ', ' + repr(self.branches)
        else:
            branches_str = ''
        return 'Tree({0}{1})'.format(self.label, branches_str)

    def is_leaf(self):
        return not self.branches

    def __eq__(self, other):
        return type(other) is type(self) and self.label == other.label \
               and self.branches == other.branches

def print_tree(t, indent=0):
    """Print a representation of this tree in which each node is
    indented by two spaces times its depth from the label.

    >>> print_tree(Tree(1))
    1
    >>> print_tree(Tree(1, [Tree(2)]))
    1
      2
    >>> numbers = Tree(1, [Tree(2), Tree(3, [Tree(4), Tree(5)]), Tree(6, [Tree(7)])])
    >>> print_tree(numbers)
    1
      2
      3
        4
        5
      6
        7
    """
    print('  ' * indent + str(t.label))
    for b in t.branches:
        print_tree(b, indent + 1)