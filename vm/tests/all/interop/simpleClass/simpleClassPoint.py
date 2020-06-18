#simpleClass.py
import math

class Point:
	def __init__(self, x, y):
		self.x=x
		self.y=y
	
	def getX(self):
		return self.x
	
	def getY(self):
		return self.y
	
	def setX(self, val):
		self.x=val

	def setY(self, val):
		self.y=val

	def printMe(self):
		print("Point: x="+str(self.x)+", y="+str(self.y))
	
	def distanceTo(self, other) {
		dX = self.x - other.x
		dY = self.y - other.y
		return math.sqrt(dX*dX+dY*dY)
	}


