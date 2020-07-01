//JS
function printFooResult(polyglot_ptr) {
	llvmFile = Polyglot.evalFile("llvm", "simpleMethodCall2.so");
	console.log("[JS] ", llvmFile.foo());
}
