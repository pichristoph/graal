//inheritMethods

function check(nErrors, info, expected, actual) {
	if(expected!=actual) {
		console.log(info, actual);
		nErrors++;
	}
	return nErrors;
}

var jsFile = Polyglot.evalFile("js", "inheritMethods.js");
var pyFile = Polyglot.evalFile("python", "inheritMethods.py");
var llFile = Polyglot.evalFile("llvm", "inheritMethods.so");

nErrors = 0;

js_add2 = new jsFile.ConstAdder(2);
js_mult3 = new jsFile.ConstMultiplier(3);

nErrors = check(nErrors, "JS: f(-, ()->2)=", 2, js_add2.getConstObj());
nErrors = check(nErrors, "JS: f(-, ()->3, inherited)=", 3, js_mult3.getConstObj());
nErrors = check(nErrors, "JS: f(5, x->x+2)=", 7, js_add2.process(5));
nErrors = check(nErrors, "JS: f(7, x->x*3)=", 21, js_mult3.process(7));

py_add2 = new pyFile.ConstAdder(2);
py_mult3 = new pyFile.ConstMultiplier(3);

nErrors = check(nErrors, "Python: f(-, ()->2)=", 2, py_add2.getConstObj());
nErrors = check(nErrors, "Python: f(-, ()->3, inherited)=", 3, py_mult3.getConstObj());
nErrors = check(nErrors, "Python: f(5, x->x+2)=", 7, py_add2.process(5));
nErrors = check(nErrors, "Python: f(7, x->x*3)=", 21, py_mult3.process(7));

ll_add2 = new llFile.ConstAdder(2);
ll_mult3 = new llFile.ConstMultiplier(3);

nErrors = check(nErrors, "C++/LLVM: f(-, ()->2)=", 2, ll_add2.getConstObj());
nErrors = check(nErrors, "C++/LLVM: f(-, ()->3, inherited)=", 3, ll_mult3.getConstObj());
nErrors = check(nErrors, "C++/LLVM: f(5, x->x+2)=", 7, ll_add2.process(5));
nErrors = check(nErrors, "C++/LLVM: f(7, x->x*3)=", 21, ll_mult3.process(7));

if(nErrors == 0) {
	console.log("OK");
} else {
	console.log(nErrors, " errors");
}
