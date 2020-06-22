//inheritMethods.js

var jsFile = Polyglot.evalFile("js", "inheritMethodsClass.js");
var pyFile = Polyglot.evalFile("python", "inheritMethodsClass.py");
var llFile = Polyglot.evalFile("llvm", "inheritMethodsClass.so");


js_add2 = new jsFile.ConstAdder(2);
js_mult3 = new jsFile.ConstMultiplier(3);

console.log("f(-, ()->2)=", js_add2.getConstObj());
console.log("f(-, ()->3, inherited)=", js_mult3.getConstObj());
console.log("f(5, x->x+2)=", js_add2.process(5));
console.log("f(7, x->x*3)=", js_mult3.process(7));

py_add2 = new pyFile.ConstAdder(2);
py_mult3 = new pyFile.ConstMultiplier(3);

console.log("f(-, ()->2)=", py_add2.getConstObj());
console.log("f(-, ()->3, inherited)=", py_mult3.getConstObj());
console.log("f(5, x->x+2)=", py_add2.process(5));
console.log("f(7, x->x*3)=", py_mult3.process(7));

ll_add2 = new llFile.ConstAdder(2);
ll_mult3 = new llFile.ConstMultiplier(3);

console.log("f(-, ()->2)=", ll_add2.getConstObj());
console.log("f(-, ()->3, inherited)=", ll_mult3.getConstObj());
console.log("f(5, x->x+2)=", ll_add2.process(5));
console.log("f(7, x->x*3)=", ll_mult3.process(7));

