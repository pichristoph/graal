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
