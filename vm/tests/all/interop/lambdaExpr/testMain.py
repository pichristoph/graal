#lambdaExpr.py
import polyglot

def check(nErrors, info, expected, actual):
	if(expected!=actual):
		print(info+str(actual))
		nErrors=nErrors+1
	return nErrors

llFile = polyglot.evalFile("llvm", "lambdaExpr.so")
pyFile = polyglot.evalFile("python", "lambdaExpr.py")
jsFile = polyglot.evalFile("js", "lambdaExpr.js")

nErrors = 0

c = llFile.MyClass()
nErrors = check(nErrors, "C++/LLVM: calling f(8, x->x) leads to ", 8, c.foo(8))
c.foo = lambda x: x*2+1
nErrors = check(nErrors, "C++/LLVM: calling f(8, x->2*x+1) leads to ", 17, c.foo(8))

cJ = jsFile.MyClass()
nErrors = check(nErrors, "JS: calling f(8, x->x) leads to ", 8, cJ.foo(8))
cJ.foo = lambda x: x*2+1
nErrors = check(nErrors, "JS: calling f(8, x->2*x+1) leads to ", 17, cJ.foo(8))

cP = pyFile.MyClass()
nErrors = check(nErrors, "Python: calling f(8, x->x) leads to ", 8, cP.foo(8))
cP.foo = lambda x: x*2+1
nErrors = check(nErrors, "Python: calling f(8, x->2*x+1) leads to ", 17, cP.foo(8))

if(nErrors==0):
	print("OK")
else:
	print(str(nErrors)+" errors.")
