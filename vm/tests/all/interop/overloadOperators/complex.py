#complex.py


class ComplexNumber:
	def __init__(self, re, im):
		self.re = re
		self.im = im


	def __add__(self, other):
		return self.re+other.re, self.im + other.im



