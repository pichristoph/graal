//JS
class MyClass {
	foo() {
		return 749;
	}
}

llvmFile = Polyglot.evalFile("llvm", "simpleMethodCall1.so");
myClassObj = new MyClass();
console.log("[JS] Now, it should print \"749\": ");
llvmFile.printFooResult(myClassObj);
