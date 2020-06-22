#inheritMemberClass.py

class LinearFunction:
	
	def __init__(self, k, d):
		self.k=k
		self.d=d

	def evaluate(self, x):
		return self.k*x+self.d
	


class ConstFunction (LinearFunction):
	def __init__(self, d) {
		super().__init__(self, 0, d)
	}

