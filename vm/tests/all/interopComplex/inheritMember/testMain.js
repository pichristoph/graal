//inheritMember

nErrors = 0;
var jsFile = Polyglot.evalFile("js", "inheritMember.js");
var pyfile = Polyglot.evalFile("python", "inheritMember.py");
var llvmFile = Polyglot.evalFile("llvm", "inheritMember.so");

js_m4p2 = new jsFile.LinearFunction(4, 2);
js_c3 = new jsFile.ConstFunction(5);
py_m4p2 = new pyFile.LinearFunction(4, 2);
py_c3 = new pyFile.ConstFunction(5);
ll_m4p2 = new llvmFile.LinearFunction(4, 2);
ll_c3 = new llvmFile.ConstFunction(5);

val = js_idP2.evaluate(3);
if(val != 14) {
	console.log("ERROR! JS: f(3, x->4x+2)=", val);
	nErrors++;
}

val = js_c3.evaluate(2);
if(val != 5) {
	console.log("ERROR! JS: f(2, x->5)=", val);
	nErrors++;
}

val = py_m4p2.evaluate(3);
if(val != 14) {
	console.log("ERROR! Python: f(3, x->4x+2)=", val);
	nErrors++;
}

val = py_c3.evaluate(2);
if(val != 5) {
	console.log("ERROR! Python: f(2, x->5)=", val);
	nErrors++;
}

val = ll_idP2.evaluate(3);
if(val != 14) {
	console.log("ERROR! C++/LLVM: f(3, x->4x+2)=", val);
	nErrors++;
}

val = ll_c3.evaluate(2);
if(val != 5) {
	console.log("ERROR! C++/LLVM: f(2, x->5)=", val);
	nErrors++;
}

if(nErrors==0) {
	console.log("OK");
}


