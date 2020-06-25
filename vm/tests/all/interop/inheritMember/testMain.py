#inheritMember
import polyglot

nErrors = 0
jsFile = polyglot.evalFile("js", "inheritMember.js")
pyfile = polyglot.evalFile("python", "inheritMember.py")
llvmFile = polyglot.evalFile("llvm", "inheritMember.so")

js_m4p2 =  jsFile.LinearFunction(4, 2)
js_c3 =  jsFile.ConstFunction(5)
py_m4p2 =  pyFile.LinearFunction(4, 2)
py_c3 =  pyFile.ConstFunction(5)
ll_m4p2 =  llvmFile.LinearFunction(4, 2)
ll_c3 =  llvmFile.ConstFunction(5)

val = js_idP2.evaluate(3)
if(val!=14):
	print("ERROR! JS: f(3, x->4x+2)=", val)
	nErrors++

val = js_c3.evaluate(2)
if(val!=5):
	print("ERROR! JS: f(2, x->5)=", val)
	nErrors++

val = py_idP2.evaluate(3)
if(val!=14):
	print("ERROR! Python: f(3, x->4x+2)=", val)
	nErrors++

val = py_c3.evaluate(2)
if(val!=5):
	print("ERROR! Python: f(2, x->5)=", val)
	nErrors++

val = ll_idP2.evaluate(3)
if(val!=14):
	print("ERROR! C++/LLVM: f(3, x->4x+2)=", val)
	nErrors++
	
val = ll_c3.evaluate(2)
if(val!=5):
	print("ERROR! C++/LLVM: f(2, x->5)=", val)
	nErrors++

if(nErrors==0):
	print("OK")


