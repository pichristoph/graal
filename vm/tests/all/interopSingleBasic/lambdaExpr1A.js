//JS

class AClass() {
	constructor() {
		this.foo = (x => x);
	}
}

llvmFile = Polyglot.evalFile("llvm", "lambdaExpr1.so");

aObj = new AClass();
val = llvmFile.evaluate(aObj, 4);
console.log("[JS] calling LLVM identity (x -> x) of 4 leads to: ", val);
aObj.foo = (x => 2*x-1);
val = llvmFile.evaluate(aObj, 4);
console.log("[JS] calling LLVM (x -> 2x-1) of 4 leads to: ", val);
