//JS

class ParentClass {
	constructor() {
		this.val = 0;
	}
}

class ChildClass extends ParentClass {
	constructor() {
		super();
	}
	setVal(val) {
		super.val = val;
	}
};

obj = new ChildClass();
obj.setVal(4);
llvmFile = Polyglot.evalFile("llvm", "inheritMembers1.so");
llvmFile.processAndEvaluate(obj, 6);


