//inheritMethodsClass.js

class ConstAdder {

	constructor(x) {
		this.constObj = x;
	}

	process(y) {
		return y+this.constObj;
	}

	getConstObj() {
		return this.constObj;
	}
}

class ConstMultiplier extends ConstAdder {
	constructor(x) {
		super(x);
	}

	process(y) {
		return y*this.constObj;
	}
}
