//JS

class A {
	foo1() {
		console.log("A::foo1()");
	}
	foo2() {
		console.log("A::foo2()");
	}
}

class B extends A {
	foo2() {
		console.log("B::foo2()");
	}
}

function createB() {
	return new B();
}

function createA() {
	return new A();
}
