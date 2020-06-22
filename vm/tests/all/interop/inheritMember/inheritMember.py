#inheritMember.py
import polyglot

jsFile = polyglot.evalFile("js", "inheritMemberClass.js")
pyfile = polyglot.evalFile("python", "inheritMemberClass.py")
llvmFile = polyglot.evalFile("llvm", "inheritMemberClass.so")

js_m4p2 =  jsFile.LinearFunction(4, 2)
js_c3 =  jsFile.ConstFunction(5)
py_m4p2 =  pyFile.LinearFunction(4, 2)
py_c3 =  pyFile.ConstFunction(5)
ll_m4p2 =  llvmFile.LinearFunction(4, 2)
ll_c3 =  llvmFile.ConstFunction(5)

print("JS: f(3, x->4x+2)=", js_idP2.evaluate(3))
print("JS: f(2, x->5)=", js_c3.evaluate(2))
print("Py: f(3, x->4x+2)=", py_idP2.evaluate(3))
print("Py: f(2, x->5)=", py_c3.evaluate(2))
print("C++/LLVM: f(3, x->4x+2)=", ll_idP2.evaluate(3))
print("C++/LLVM: f(2, x->5)=", ll_c3.evaluate(2))





