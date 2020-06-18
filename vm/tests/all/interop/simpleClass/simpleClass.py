#simpleClass.py

import polyglot

llvmFile = polyglot.evalFile("llvm","simpleClassPoint.so")
pyFile = polyglot.evalFile("python", "simpleClassPoint.py")
jsFile = polyglot.evalFile("js", "simpleClassPoint.js")

lp1 = llvmFile.Point(4, 5)
pp2 = pyFile.Point(1, 9)
pp1 = pyFile.Point(lp1.getX(), lp1.getY())
lp2 = llvmFile.Point(pp2.getX(), pp2.getY())
jp1 = jsFile.Point(4, 5)
jp2 = jsFile.Point(1, 9)

ld = lp1.distanceTo(lp2)
pd = pp2.distanceTo(pp1)
jd = jp1.distanceTo(jp2)


print("LLVM Points: ")
lp1.printMe()
lp2.printMe()
print("Python Points: ")
pp1.printMe()
pp2.printMe()
print("JavaScript Points: ")
jp1.printMe()
jp2.printMe()

print("LLVM Point distance (should be 5): "+str(ld))
print("JavaScript Point distance (should be 5): "+str(jd))
print("Python Point distance (should be 5): "+str(pd))

#optional
mixed = lp1.distanceTo(pp2)
print("Distance between LLVM and Python point, should be 5: "+str(mixed))

