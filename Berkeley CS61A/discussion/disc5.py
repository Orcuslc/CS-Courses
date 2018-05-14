True
False
True
[1, 2, 3, 4]
[1, 2, 3, 4]
[1, 42, 3, 4]
False
[1, 42, 3, 4, 5]
[1, 42, 3, 4]
False

def remove_all(el, lst):
	i = len(lst)-1
	while i >= 0:
		if lst[i] == el:
			lst.pop(i)
		i -= 1

def square_elements(lst):
	for i in range(len(lst)):
		lst[i] = lst[i]**2

"Dumbledore is awesome!"
"Dumbledore is awesome!"
"Thanks, Hagrid"
2
2
"Umbridge is awesome!"

class Cat(Pet):
	def __init__(self, name, owner, lives = 9):
		super().__init__(name, owner)
		self.lives = lives

	def talk(self):
		print(self.name + ' says meow!')

	def lose_life(self):
		if self.lives > 0:
			self.lives -= 1
		else:
			self.is_alive = False

class NoisyCat(Cat):
	def __init__(self, name, owner, lives = 9):
		super().__init__(name, owner, lives)

	def talk(self):
		print(self.name + ' says meow!')
		print(self.name + ' says meow!')

2
4
4
8

class Yolo:
	def __init__(self, x):
		self.x = x
		self.motto = 0

	def g(self, y):
		if self.motto:
			return self.motto + y
		else:
			return self.x + y