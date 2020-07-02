//JS


llvmFile = Polyglot.evalFile("llvm", "exception1.so");
try {
	val = llvmFile.run(3);	//calculate 8/3
	console.log("[JS] Should print LLVM-calculated value 2: ", val);

	val = llvmFile.run(0);	//calculate 8/0
	console.log("[JS] This should not be printed! Exception thrown by LLVM has not been caught!");
} catch(e) {
	console.log("[JS] Intentionally LLVM-thrown exception has been caught as planned!");
}
