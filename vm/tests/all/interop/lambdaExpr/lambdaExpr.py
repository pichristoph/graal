#lambdaExpr.py
import polyglot

llFile = polyglot.evalFile("llvm", "lambdaExprClass.so")
pyFile = polyglot.evalFile("python", "lambdaExprClass.py")
jsFile = polyglot.evalFile("js", "lambdaExprClass.js")

c = llFile.MyClass()
print("calling f(8, x->x) leads to ", c.foo(8))
c.foo = lambda x: x*2+1
print("calling f(8, x->2*x+1) leads to ", c.foo(8))

cJ = jsFile.MyClass()
print("calling f(8, x->x) leads to ", cJ.foo(8))
cJ.foo = lambda x: x*2+1
print("calling f(8, x->2*x+1) leads to ", cJ.foo(8))

cP = pyFile.MyClass()
print("calling f(8, x->x) leads to ", cP.foo(8))
cP.foo = lambda x: x*2+1
print("calling f(8, x->2*x+1) leads to ", cP.foo(8))
