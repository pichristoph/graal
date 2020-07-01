//inheritMemberClass.js

class LinearFunction {
	
	constructor(kVal, dVal) {
		this.k=kVal;
		this.d=dVal;
	}

	evaluate(x) {
		return this.k*x+this.d;
	}
}

class ConstFunction extends LinearFunction {
	constructor(dVal) {
		super(0, dVal);
	}
}
