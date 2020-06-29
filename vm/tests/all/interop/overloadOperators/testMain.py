#overloadOperators
import polyglot

nErrors=0
llFile = polyglot.evalFile("llvm", "complex.so")
c1 = llFile.ComplexNumber(3,2)
c2 = llFile.ComplexNumber(4,5)
c3 = c1+c2
if(c3.re!=7 || c3.im != 7):
	nErrors+=1
	print("ERROR! (3,2)+(4,5)=("+str(c3.re)+ ","+str(c3.im)+ ")")	


pyFile = polyglot.evalFile("python", "complex.py")
c1 = llFile.ComplexNumber(3,2)
c2 = llFile.ComplexNumber(4,5)
c3 = c1+c2
if(c3.re!=7 || c3.im != 7):
	nErrors+=1
	print("ERROR! (3,2)+(4,5)=("+str(c3.re)+ ","+str(c3.im)+ ")")	

if(nErrors==0):
	print("OK")
