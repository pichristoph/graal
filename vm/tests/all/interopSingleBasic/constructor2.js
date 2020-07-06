//JS

class TestClass {
	constructor(x) {
		this.x=x;
	}
}

tc = new TestClass(5);
llvmFile = Polyglot.evalFile("llvm", "constructor2.so");
llvmFile.printX(tc);

