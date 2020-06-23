#references.py
import polyglot

llFile = polyglot.evalFile("llvm", "referencesClass.cpp")

c = llFile.MyClass()
c.i = 3
ref = c.getRef()
ref = 4
print("reference to c.i has been set to 4. c.i=", c.i)
