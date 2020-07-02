//JS

llvmFile = Polyglot.evalFile("llvm", "arrays1.so");

arr = llvmFile.getSquaredArray(4);
console.log("[JS] LLVM-Array with length 4 (actual: ", arr.length, "), and arr[3] = 9 (actual: ", arr[3], ")");
