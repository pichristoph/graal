//lambdaExpr.js

var llFile = Polyglot.evalFile("llvm", "lambdaExprClass.so");
var jsFile = Polyglot.evalFile("js", "lambdaExprClass.js");
var pyFile = Polyglot.evalFile("python", "lambdaExprClass.py");

c = new llFile.MyClass();
console.log("calling f(8, x->x) leads to ", c.foo(8));
c.foo = (x => x*2+1);
console.log("calling f(8, x->2*x+1) leads to ", c.foo(8));

cJ = new jsFile.MyClass();
console.log("calling f(8, x->x) leads to ", cP.foo(8));
cJ.foo = (x => x*2+1);
console.log("calling f(8, x->2*x+1) leads to ", cJ.foo(8));

cP = new pyFile.MyClass();
console.log("calling f(8, x->x) leads to ", cP.foo(8));
cP.foo = (x => x*2+1);
console.log("calling f(8, x->2*x+1) leads to ", cP.foo(8));
