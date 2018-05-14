def square_tree(t):
	if is_leaf(t):
		return tree(label(t)**2)
	else:
		return tree(label(t)**2, map(square_tree, branches(t)))

def height(t):
	if is_leaf(t):
		return 1
	else:
		return max(list(map(height, branches(t)))) + 1

def tree_max(t):
	if is_leaf(t):
		return label(t)
	else:
		return max(list(map(tree_max, branches(t))), label(t))

def find_path(tree, x):
	nonlocal res
	if is_label(tree):
		if label(tree) == x:
			return [x]
		else:
			return []
	childres = list(filter(lambda x: x is not None, map(find_path, branches(tree))))
	if childres is not None:
		return [label(tree)] + childres
	else:
		return []

def prune(t, k):
	if k == 0:
		return tree(label(t))
	return tree(label(t), [prune(i, k-1) for i in branches(t)])

def hailstone(n, h):
	if h == 1:
		return tree(n)
	if (n-1)%3 == 0 and ((n-1)//3)%2 == 1 and n > 4:
		return tree(n, [hailstone(2*n, h-1), hailstone((n-1)//3, h-1)])
	else:
		return tree(n, [hailstone(2*n, h-1)])
