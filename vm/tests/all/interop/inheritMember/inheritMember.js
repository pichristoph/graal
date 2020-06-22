//inheritMember.js

var jsFile = Polyglot.evalFile("js", "inheritMemberClass.js");
var pyfile = Polyglot.evalFile("python", "inheritMemberClass.py");
var llvmFile = Polyglot.evalFile("llvm", "inheritMemberClass.so");

js_m4p2 = new jsFile.LinearFunction(4, 2);
js_c3 = new jsFile.ConstFunction(5);
py_m4p2 = new pyFile.LinearFunction(4, 2);
py_c3 = new pyFile.ConstFunction(5);
ll_m4p2 = new llvmFile.LinearFunction(4, 2);
ll_c3 = new llvmFile.ConstFunction(5);

console.log("JS: f(3, x->4x+2)=", js_idP2.evaluate(3));
console.log("JS: f(2, x->5)=", js_c3.evaluate(2));
console.log("Py: f(3, x->4x+2)=", py_idP2.evaluate(3));
console.log("Py: f(2, x->5)=", py_c3.evaluate(2));
console.log("C++/LLVM: f(3, x->4x+2)=", ll_idP2.evaluate(3));
console.log("C++/LLVM: f(2, x->5)=", ll_c3.evaluate(2));





