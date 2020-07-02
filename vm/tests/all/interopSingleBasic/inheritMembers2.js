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
	evaluate(x) {
		return x*val;
	}
};

