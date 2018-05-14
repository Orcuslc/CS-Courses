"""
1. O(n^2)
2. O(((sqrt(5)+1)/2)^n)
3. O(n)
4. O(1)
5. O(log n)
6. same with 2
"""

def make_even(t):
	if t.label % 2 == 1:
		t.lable += 1
	if not is_leaf(t):
		for br in t.branches:
			make_even(br)

def fill_tree(t, n):
	t.label = n
	if not is_leaf(t):
		for br in t.branches:
			fill_tree(t, n)

def combine_tree(t1, t2, combiner):
	label = combiner(t1.label. t2.label)
	branches = []
	if not is_leaf(t):
		for i in range(len(t1.branches)):
			branches.append(combine_tree(t1.branches[i], t2.branches[i], combiner))
	return Tree(label, branches)

def average(t):
	def helper(t, asum, count):
		asum += t.label
		count += 1
		if not is_leaf(t):
			for br in t.branches:
				asum, count = helper(br, asum, count)
		return asum, count
	asum, count = helper(t, 0, 0)
	return asum / count

def alt_tree_map(t, map_fn):
	t.label = map_fn(t.label)
	if not is_leaf(t):
		for br in t.branches:
			alt_tree_map(br, map_fn)

def first_to_last(self, other):
	def helper(t1, t2):
		if not self.is_leaf(t1):
			br1 = t1.branches[-1]
			br2 = t2.branches[-1]
			b1, b2 = helper(br1, br2)
			t1.branches[-1] = b1
			t2.branches[-1] = b2
			b1.parent = t1
			b2.parent = t2
		return t1, t2
	return helper(self.root, other)
