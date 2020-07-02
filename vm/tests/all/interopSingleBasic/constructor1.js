//JS

llvmFile = Polyglot.evalFile("js", "constructor2.js");
testClassObj = new llvmFile.TestClass(9);
console.log("[JS] Object created with LLVM, field value should be 9: ", testClassObj.getX()); 
