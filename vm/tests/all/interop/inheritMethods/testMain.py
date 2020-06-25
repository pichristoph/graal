#inheritMethods
import polyglot

def check(nErrors, info, expected, actual):
	if(expected!=actual):
		print(info+str(actual))
		nErrors++
	return nErrors

nErrors = 0
jsFile = polyglot.evalFile("js", "inheritMethods.js")
pyFile = polyglot.evalFile("python", "inheritMethods.py")
llFile = polyglot.evalFile("llvm", "inheritMethods.so")


js_add2 = jsFile.ConstAdder(2)
js_mult3 = jsFile.ConstMultiplier(3)

nErrors = check(nErrors, "JS: f(-, ()->2)=", 2, js_add2.getConstObj())
nErrors = check(nErrors, "JS: f(-, ()->3, inherited)=", 3, js_mult3.getConstObj())
nErrors = check(nErrors, "JS: f(5, x->x+2)=", 7, js_add2.process(5))
nErrors = check(nErrors, "JS: f(7, x->x*3)=", 21, js_mult3.process(7))

py_add2 = pyFile.ConstAdder(2)
py_mult3 = pyFile.ConstMultiplier(3)

nErrors = check(nErrors, "Python: f(-, ()->2)=", 2, py_add2.getConstObj())
nErrors = check(nErrors, "Python: f(-, ()->3, inherited)=", 3, py_mult3.getConstObj())
nErrors = check(nErrors, "Python: f(5, x->x+2)=", 7, py_add2.process(5))
nErrors = check(nErrors, "Python: f(7, x->x*3)=", 21, py_mult3.process(7))

ll_add2 = llFile.ConstAdder(2)
ll_mult3 = llFile.ConstMultiplier(3)

nErrors = check(nErrors, "C++/LLVM: f(-, ()->2)=", 2, ll_add2.getConstObj())
nErrors = check(nErrors, "C++/LLVM: f(-, ()->3, inherited)=", 3, ll_mult3.getConstObj())
nErrors = check(nErrors, "C++/LLVM: f(5, x->x+2)=", 7, ll_add2.process(5))
nErrors = check(nErrors, "C++/LLVM: f(7, x->x*3)=", 21, ll_mult3.process(7))

if(nErrors==0):
	print("OK")
else:
	print(str(nErrors)+" errors")
