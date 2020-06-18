//simpleClassPoint.js

class Point {
	constructor(x, y) {
		this.x=x;
		this.y=y;
	}
	
	getX() {
		return this.x;
	}
	getY() {
		return this.y;
	}
	setX(val) {
		this.x=val;
	}
	setY(val) {
		this.y=val;
	}
	printMe() {
		console.log("Point: x=", this.x, ", y=", this.y);
	}
	distanceTo(other) {
		dX = this.x - other.x;
		dY = this.y - other.y;
		return Math.sqrt(dX*dX+dY*dY);
	}
};

