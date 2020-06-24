#overloadOperators.py
import polyglot

llFile = polyglot.evalFile("llvm", "complex.so")
c1 = llFile.Complex(3,2)
c2 = llFile.Complex(4,5)
c3 = c1+c2
print("(3,2)+(4,5)=(", c3.re, ",", c3.im, ")")

pyFile = polyglot.evalFile("python", "complex.py")
c1 = llFile.ComplexNumber(3,2)
c2 = llFile.ComplexNumber(4,5)
c3 = c1+c2
print("(3,2)+(4,5)=("+str(c3.re)+","+ str(c3.im)+")")

