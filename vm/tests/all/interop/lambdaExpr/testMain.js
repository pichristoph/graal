//lambdaExpr.js

function check(nErrors, info, expected, actual) {
	if(expected!=actual) {
		console.log(info, actual);
		nErrors++;
	}
	return nErrors;
}

var llFile = Polyglot.evalFile("llvm", "lambdaExprClass.so");
var jsFile = Polyglot.evalFile("js", "lambdaExprClass.js");
var pyFile = Polyglot.evalFile("python", "lambdaExprClass.py");

nErrors = 0;

c = new llFile.MyClass();
nErrors = check(nErrors, "calling f(8, x->x) leads to ", 8, c.foo(8));
c.foo = (x => x*2+1);
nErrors = check(nErrors, "calling f(8, x->2*x+1) leads to ", 17, c.foo(8));

cJ = new jsFile.MyClass();
nErrors = check(nErrors, "calling f(8, x->x) leads to ", 8, cP.foo(8));
cJ.foo = (x => x*2+1);
nErrors = check(nErrors, "calling f(8, x->2*x+1) leads to ", 17, cJ.foo(8));

cP = new pyFile.MyClass();
nErrors = check(nErrors, "calling f(8, x->x) leads to ", 8,  cP.foo(8));
cP.foo = (x => x*2+1);
nErrors = check(nErrors, "calling f(8, x->2*x+1) leads to ",17,  cP.foo(8));

if(nErrors==0) {
	console.log("OK");
} else {
	console.log(nErrors, " errors.");
}
