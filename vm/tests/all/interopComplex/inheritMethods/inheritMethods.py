#inheritMethodsClass.py

class ConstAdder:

	def __init__(self, x):
		self.constObj = x
	
	def process(self, y):
		return y+self.constObj

	def getConstObj(self):
		return self.constObj


class ConstMultiplier(ConstAdder):

	def __init__(self, x):
		ConstAdder.__init__(self, x)
	
	def process(self, y):
		return y*self.constObj
