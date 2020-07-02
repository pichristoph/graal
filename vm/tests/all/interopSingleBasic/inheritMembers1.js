//JS

llvmFile = Polyglot.evalFile("llvm", "inheritMembers1.so");
childObj = new llvmFile.ChildClass();
childObj.setVal(4);
console.log("[JS] Using LLVM member inheritance, result should be 20: ", childObj.evaluate(5));

