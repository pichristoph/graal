#references.py
import polyglot

llFile = polyglot.evalFile("llvm", "references.cpp")

c = llFile.MyClass()
c.i = 3
ref = c.getRef()
ref = 4
if(c.i==4):
	print("OK")
else:
	print("Error: 0 of 1 passed. c.i should be 4, but is "+str(c.i))
