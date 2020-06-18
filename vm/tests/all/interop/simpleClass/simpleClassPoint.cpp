//simpleClass.cpp
#include<iostream.h>
#include<polyglot.h>
#include<math.h>

class Point {
	private:
	int x;
	int y;
	public:
	int getX();
	int getY();
	void setX(int dX);
	void setY(int dY);
	double distanceTo(Point* other);
	void printMe();
};

POLYGLOT_DECLARE_CLASS(Point);

int Point::getX() {
	return x;
}

int Point::getY() {
	return y;
}

void Point::setX(int dX) {
	x=dX;
}

void Point::setY(int dY) {
	y=dY;
}

void Point::printMe() {
	cout << "Point: x=" << x << ", y=" << endl;
}

double distanceTo(Point* other) {
	double dX = x - other->x;
	double dY = y - other->y;
	return sqrt(dX*dX+dY*dY);
}

