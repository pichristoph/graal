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

nErrors=0

if(not lp1.checkMe(4, 5)):
	nErrors+=1
	print("ERROR! C++/LLVM: p1.y="+str(lp1.getY())+", p1.x="+str(lp1.getX()))
if(not lp2.checkMe(1, 9)):
	nErrors+=1
	print("ERROR! C++/LLVM: p2.y="+str(lp2.getY())+", p2.x="+str(lp2.getX()))
if(not pp1.checkMe(4, 5)):
	nErrors+=1
	print("ERROR! Python: p1.y="+str(pp1.getY())+", p1.x="+str(pp1.getX()))
if(not pp2.checkMe(1, 9)):
	nErrors+=1
	print("ERROR! Python: p2.y="+str(pp2.getY())+", p2.x="+str(pp2.getX()))
if(not lp1.checkMe(4, 5)):
	nErrors+=1
	print("ERROR! JS: p1.y="+str(jp1.getY())+", p1.x="+str(jp1.getX()))
if(not lp2.checkMe(1, 9)):
	nErrors+=1
	print("ERROR! JS: p2.y="+str(jp2.getY())+", p2.x="+str(jp2.getX()))

if(ld!=5 || jd != 5 || pd != 5):
	nErrors+=1
	print("LLVM Point distance (should be 5): "+str(ld))
	print("JavaScript Point distance (should be 5): "+str(jd))
	print("Python Point distance (should be 5): "+str(pd))

#optional
mixed = lp1.distanceTo(pp2)
if(mixed!=5):
	print("Distance between LLVM and Python point, should be 5: "+str(mixed))
	nErrors+=1

if(nErrors==0):
	print("OK")
else:
	print(str(nErrors)+ " errors.")

