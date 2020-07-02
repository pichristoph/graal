//JS

llvmFile = Polyglot.evalFile("llvm", "lambdaExpr1.so");

aObj = new llvmFile.AClass();
val = aObj.foo(4);
console.log("[JS] calling LLVM identity (x -> x) of 4 leads to: ", val);
aObj.foo = (x => 2*x-1);
val = aObj.foo(4);
console.log("[JS] calling LLVM (x -> 2x-1) of 4 leads to: ", val);
