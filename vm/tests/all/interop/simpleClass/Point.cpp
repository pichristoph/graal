//Point.cpp
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
	int checkMe(int dX, int dY);
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

int Point::checkMe(int dX, int dY) {
	return dX==x && dY==y;
}

double distanceTo(Point* other) {
	double dX = x - other->x;
	double dY = y - other->y;
	return sqrt(dX*dX+dY*dY);
}

