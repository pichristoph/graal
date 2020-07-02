//JS

llvmFile = Polyglot.evalFile("llvm", "inheritMethods1.so");

a = new llvmFile.A(); //has methods foo1(), foo2()
b = new llvmFile.B(); //B extends A, has method foo2() only

console.log("a.foo1() should lead to: A::foo1");
a.foo1();
console.log("b.foo1() should lead to: A::foo1");
a.foo1();
console.log("a.foo2() should lead to: A::foo2");
a.foo2();
console.log("b.foo2() should lead to: B::foo2");
a.foo2();
