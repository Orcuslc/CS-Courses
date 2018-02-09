def max_product(lst):
	if lst == []:
		return 1
	if len(lst) == 2:
		return max(lst)
	return max(lst[0]*max_product(lst[2:]), max_product(lst[1:]))

def foo(lst):
	return [i*lst[i] for i in range(0, len(lst), 2)]

def paths(m, n):
	if m == 1 or n == 1:
		return 1
	return paths(m-1, n)+paths(m, n-1)

def eval_tree(tree):
	if is_leaf(tree):
		return label(tree)
	if label(tree) == '+':
		return sum([eval_tree(b) for b in branches(tree)])
	if label(tree) == '*':
		return prod([eval_tree(b) for b in branches(tree)])

def memory(x, f):
	def g(h):
		print()
		return  
	return g

if __name__ == '__main__':
	print(max_product([5,10,5,10,5]))
	print(foo([1,2,3,4,5,6]))
	print(paths(2, 2))