#Point.py
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

	def checkMe(self, x, y):
		return self.x==x and self.y==y
	
	def distanceTo(self, other) {
		dX = self.x - other.x
		dY = self.y - other.y
		return math.sqrt(dX*dX+dY*dY)
	}


