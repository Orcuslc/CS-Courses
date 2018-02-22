class Naturals():
	def __init__(self):
		self.current = 0

	def __next__(self):
		result = self.current
		self.current += 1
		return result

	def __iter__(self):
		return self

class IteratorCombiner:
	def __init__(self, iter1, iter2, combiner):
		self.iter1 = iter1
		self.iter2 = iter2
		self.combiner = combiner

	def __next__(self):
		return self.combiner(next(self.iter1), next(self.iter2))

	def __iter__(self):
		return self

class FibIterator:
	def __init__(self):
		self.prev = 0
		self.curr = 1

	def __next__(self):
		result = self.curr 
		self.curr += self.prev
		self.prev = result
		return result

	def __iter__(self):
		return self

def perfect_squares():
	curr = 1
	while True:
		yield curr**2
		curr += 1

class Link:
	empty = ()
	def __init__(self, first, rest = empty):
		self.first = first
		self.rest = rest

	def __iter__(self):
		while self.first != empty:
			yield self.first
			self.first = first(self.rest)
			self.rest = rest(self.rest)

def generate_subsets():
	called = 0
	curr = [[]]
	while 1:
		called += 1
		yield curr
		curr = curr + [i + [called] for i in curr]

def baththub(n):
	def ducky_annihilator(rate):
		def ducky():
			nonlocal n
			n -= rate
			print(n, 'rubber duckies left')
		return ducky
	return ducky_annihilator