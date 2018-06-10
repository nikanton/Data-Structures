#include <algorithm>
#include <math.h>
#include <stack>
double precision = 0.000000001; //precision of calculations
bool between(double a, double x1, double x2) { //Funtion checks the position of a. True if it's between x1 & x2 inclusive, else false.
	if (x2 < x1) std::swap(x1, x2);
	return (x1 <= a && a <= x2 ? true : false);
}
class Vector;
class Point;
class Line;
class Segment;
class Ray;
class Polygon;

class Vector {
	friend class Point;
	friend class Line;
	friend class Segment;
	friend class Ray;
	friend class Polygon;
private:
	double x;
	double y;
public:
	Vector(Line&); //makes direction vector of line
	Vector(const Point &initialPoint, const Point &terminalPoint);
	Vector(Point &terminalPoint);
	Vector(double x, double y) : x(x), y(y) {}
	Vector(const Vector&);
	double getX() { return x; }
	double getY() { return y; }
	Vector operator+(const Vector&);
	Vector operator-(const Vector&);
	double operator*(const Vector&); //scalar product
	Vector operator*(double);
	Vector operator/(double);
	double cos(const Vector&); //calculates cosine between 2 vectors
	double sin(const Vector&); //calculates sinus between 2 vectors
	void operator=(const Vector&);
	double square(const Vector&); //scalar of vector product
	double abs();
	friend std::ostream& operator<< (std::ostream&, const Vector&);
	friend std::istream& operator>> (std::istream&, Vector&);
};

class Shape {
public:
	virtual bool contain(const Point&) = 0;
	virtual void shift(const Vector&) = 0;
	virtual bool cross(const Segment&) = 0;
};

class Point: public Shape {
	friend class Line;
	friend class Vector;
	friend class Segment;
	friend class Ray;
	friend class Polygon;
private:
	double x, y;
public:
	bool operator< (const Point&);
	bool operator== (const Point & a) { return (x == a.x && y == a.y); }
	Point(double pointX = 0., double pointY = 0.) : x(pointX), y(pointY){}
	bool contain(const Point&);
	void shift(const Vector&);
	bool cross(const Segment&);
	double getX() { return x; }
	double getY() { return y; }
	Vector makeVector(Point origin = Point(0., 0.));
	friend std::ostream& operator<< (std::ostream&, const Point&);
	friend std::istream& operator>> (std::istream&, Point&);
	friend bool cmp(const Point& a, const Point& b);
};
class Segment : public Shape {
	friend class Point;
	friend class Line;
	friend class Ray;
	friend class Polygon;
private:
	Point A, B;
public:
	Segment(const Point & a, const Point & b) : A(a), B(b){}
	Segment(double x1, double y1, double x2, double y2) : A(Point(x1, y1)), B(Point(x2, y2)){}
	bool contain(const Point&);
	void shift(const Vector&);
	bool cross(const Segment&);
	double distance(Point &);
};


class Line : public Shape {
	friend class Vector;
	friend class Ray;
private:
	double A, B, C;
public:
	Line(double tan, double place) : A(tan), C(place), B(-1.) {}
	Line(Point&, Point&);
	Line(double A, double B, double C) : A(A), B(B), C(C){}
	Line(Ray &);
	Line(Segment & a) { Line(a.A, a.B); }
	double getA() { return A; }
	double getB() { return B; }
	double getC() { return C; }
	friend std::ostream& operator<< (std::ostream&, const Line&);
	friend std::istream& operator>> (std::istream&, Line&);
	double operator() (double x, double y) { return A * x + B * y + C; }
	double operator() (const Point & p) { return A * p.x + B * p.y + C; }
	bool operator|| (const Line &);
	bool operator== (const Line &);
	Point somePoint();
	bool contain(const Point&);
	void shift(const Vector&);
	bool cross(const Segment&);
	Point crossPoint(const Line&);
	double distance(Point&);
};

class Ray : public Shape {
private:
	Point origin, direction;
public:
	Point getOrigin() { return origin; }
	Point getDirection() { return direction; }
	Ray(const Point& origin, const Point& direction) : origin(origin), direction(direction){}
	void shift(const Vector&);
	bool contain(const Point&);
	bool cross(const Segment&);
};

class Polygon : public Shape {
private:
	int numOfPoints;
	Point *points;
public:
	Polygon(int numOfPoints, Point * points) : numOfPoints(numOfPoints), points(points){}
	Polygon(Polygon &);
	~Polygon() { delete[] points; }
	void convexHull();
	int getNumOfPoints() { return numOfPoints; }
	void square();
	void shift(const Vector&);
	bool contain(const Point&);
	bool cross(const Segment&);
	bool isHullConvex();
};
//		Vector functions
Vector::Vector(const Point & initialPoint, const Point & terminalPoint) {
	x = terminalPoint.x - initialPoint.x;
	y = terminalPoint.y - initialPoint.y;
}
Vector::Vector(Point & terminalPoint) {
	x = terminalPoint.x;
	y = terminalPoint.y;
}
Vector::Vector(const Vector &a) {
	x = a.x;
	y = a.y;
}
Vector Vector::operator+(const Vector &a) {
	return Vector(x + a.x, y + a.y);
}
Vector Vector::operator-(const Vector &a) {
	return Vector(x - a.x, y - a.y);
}
double Vector::operator*(const Vector &a) {
	return x * a.x + y * a.y;
}
Vector Vector::operator*(double a) {
	return Vector(a * x, a * y);
}
Vector Vector::operator/(double a) {
	return Vector(x / a, y / a);
}
inline double Vector::cos(const Vector & a){
	return ((*this) * a) / ((*this).abs() * Vector(a).abs());
}
double Vector::sin(const Vector & a) {
	return square(a) / (abs() * Vector(a).abs());
}
void Vector::operator=(const Vector &a) {
	x = a.x;
	y = a.y;
}
double Vector::square(const Vector &a) {
	return x * a.y - y * a.x;
}
double Vector::abs() {
	return sqrt(x * x + y * y);
}
Vector::Vector(Line & a) {
	if (a.B != 0) {
		x = 1;
		y = -a.A / a.B;
		double abs = (*this).abs();
		x /= abs;
		y /= abs;
	}
	else {
		x = 0;
		y = 1;
	}
}
std::ostream & operator<<(std::ostream & os, const Vector & a) {
	os << a.x << " " << a.y;
	return os;
}

std::istream & operator >> (std::istream & is, Vector & a) {
	is >> a.x >> a.y;
	return is;
}

//		Point functions
std::ostream & operator<<(std::ostream & os, const Point & a) {
	os << a.x << " " << a.y;
	return os;
}

std::istream & operator>> (std::istream& is, Point & a) {
	is >> a.x >> a.y;
	return is;
}

bool Point::operator<(const Point & a) {
	if (x < a.x) return true;
	else if (x == a.x && y < a.y) return true;
	else return false;
}

bool Point::contain(const Point & a) {
	return (x == a.x) && (y == a.y);
}

void Point::shift(const Vector & a) {
	x += a.x;
	y += a.y;
}

bool Point::cross(const Segment & a) {
	if (Vector(a.A.x - x, a.A.y - y).square(Vector(a.B.x - x, a.B.y - y)) == 0 && between(x, a.A.x, a.B.x) && between(y, a.A.y, a.B.y))
		return true;
	else
		return false;
}

Vector Point::makeVector(Point origin) {
	return Vector(x - origin.x, y - origin.y);
}

//		Segment functions
bool Segment::contain(const Point & a) {
	if (A == a || B == a) return true;
	if (between(Vector(A.x - a.x, A.y - a.y).square(Vector(B.x - a.x, B.y - a.y)), precision, -precision) && between(a.x, A.x, B.x) && between(a.y, A.y, B.y))
		return true;
	else
		return false;
}

void Segment::shift(const Vector & a) {
	A.shift(a);
	B.shift(a);
}

bool Segment::cross(const Segment & a) {
	bool firstCondition, secondCondition, thirdCondition;
	firstCondition = ((Vector(A, B).square(Vector(A, a.A))) * (Vector(A, B).square(Vector(A, a.B)))) <= 0; //Maybe I shoud use precision variable instead of 0.
	secondCondition = ((Vector(a.A, a.B).square(Vector(a.A, A))) * (Vector(a.A, a.B).square(Vector(a.A, B)))) <= 0;
	thirdCondition = (between(A.x, a.A.x, a.B.x) || between(B.x, a.A.x, a.B.x) || between(a.B.x, A.x, B.x) || between(a.A.x, A.x, B.x)) &&
		(between(A.y, a.A.y, a.B.y) || between(B.y, a.A.y, a.B.y) || between(a.A.y, A.y, B.y) || between(a.B.y, A.y, B.y));
	return firstCondition && secondCondition && thirdCondition;
}

double Segment::distance(Point & C){
	if (Vector(A, B).cos(Vector(C, A)) * Vector(A, B).cos(Vector(C, B)) <= 0) return (Line(A, B)).distance(C);
	else return std::min(fabs(Vector(C, A).abs()), fabs(Vector(C, B).abs()));
}

//		Line functions
Line::Line(Point & a, Point & b) {
	if (b.x == a.x) {
		A = 1;
		B = 0;
		C = -a.x;
	}
	else {
		A = (b.y - a.y) / (b.x - a.x);
		B = -1;
		C = a.y - a.x * A;
	}
}

Line::Line(Ray & r) {
	Point a = r.getOrigin(), b = r.getDirection();
	if (b.x == a.x) {
		A = 1;
		B = 0;
		C = -a.x;
	}
	else {
		A = (b.y - a.y) / (b.x - a.x);
		B = -1;
		C = a.y - a.x * A;
	}
}

std::ostream & operator << (std::ostream & os, const Line & a) {
	os << a.A << " " << a.B << " " << a.C;
	return os;
}

std::istream & operator >> (std::istream & is, Line & a) {
	is >> a.A >> a.B >> a.C;
	return is;
}

bool Line::operator||(const Line & a) {
	if (A == a.A && A == 0) return true;
	else if (A * a.A == 0) return false;
	else if (B / A == a.B / a.A) return true;
	else return false;
}

bool Line::operator==(const Line & a) {
	if (A == 0) {
		if (a.A == 0 && C * a.B == a.C * B) return true;
		else return false;
	}
	else {
		if (B * a.A == a.B * A && C * a.A == a.C * A) return true;
		else return false;
	}
}

inline Point Line::somePoint() {
	if (B == 0) return Point(-C / A, 1);
	else return Point(1, -(C + A) / B);
}

bool Line::contain(const Point & a) {
	return between(A * a.x + B * a.y + C, precision, -precision);
}

void Line::shift(const Vector & a) {
	Point firstPoint = somePoint();
	firstPoint.shift(a);
	Point secondPoint = firstPoint;
	secondPoint.shift(Vector(*this));
	*this = Line(firstPoint, secondPoint);
}

bool Line::cross(const Segment & a){
	return (*this)(a.A.x, a.A.y) * (*this)(a.B.x, a.B.y) <= 0;
}

inline Point Line::crossPoint(const Line &a){
	Line & b = *this;
	return Point(-(a.C * b.B - b.C * a.B) / (a.A * b.B - b.A * a.B), -(a.A * b.C - b.A * a.C) / (a.A * b.B - b.A * a.B));
}

inline double Line::distance(Point & a) {
	return fabs((*this)(a.getX(), a.getY())) / sqrt(A * A + B * B);
}

//		Ray functions
void Ray::shift(const Vector & a){
	origin.shift(a);
	direction.shift(a);
}

bool Ray::contain(const Point & a){
	if (origin == a) return true;
	Vector rayVector(origin, direction), pointVector(origin, a);
	if (between(rayVector.cos(pointVector), 1 + precision, 1 - precision)) return true;
	else return false;
}

bool Ray::cross(const Segment & a){
	if (origin == a.A || origin == a.B) return true;
	else if (!Line(origin, direction).cross(a)) return false;
	else if (between(Vector(origin, a.A).cos(Vector(origin, a.B)), -1 + precision, -1 - precision)) return true;
	else if (between(Vector(origin, a.A).cos(Vector(origin, a.B)), 1 - precision, 1 + precision)) return false;
	else {
		Segment aCopy(a);
		Point cross = Line(origin, direction).crossPoint(Line(aCopy.A, aCopy.B));
		if (between(Vector(origin, cross).cos(Vector(origin, direction)), 1 - precision, 1 + precision)) return true;
		else return false;
	}
}

//		Polygon functions
Polygon::Polygon(Polygon &a){
	numOfPoints = a.numOfPoints;
	points = new Point[numOfPoints];
	for (int i = 0; i < numOfPoints; ++i) points[i] = a.points[i];
}

bool Polygon::isHullConvex() {
	int c = 0;
	for (int i = 2; i < numOfPoints + 2; ++i) {
		long long l = (long long)(points[(i - 1) % numOfPoints].getX() - points[(i - 2) % numOfPoints].getX()) *
			(long long)(points[i % numOfPoints].getY() - points[(i - 1) % numOfPoints].getY()) -
			(long long)(points[(i - 1) % numOfPoints].getY() - points[(i - 2) % numOfPoints].getY()) *
			(long long)(points[i % numOfPoints].getX() - points[(i - 1) % numOfPoints].getX());
		if (c == 0)
			if (l == 0) continue;
			else c = (l > 0 ? 1 : -1);
		else if (l * c < 0) return false;
	}
	return true;
}

bool cmp(const Point& a, const Point& b) {
	return a.x < b.x ||a.x == b.x && a.y < b.y;
}
void Polygon::convexHull(){
	int & n = numOfPoints;
	std::sort(points, points + n, cmp);
	Line l(points[0], points[n - 1]);
	std::stack<Point> s1;
	s1.push(points[n - 1]);
	Point toS1 = *points;
	for (int i = 1; i < n; ++i) {
		if (l(points[i].x, points[i].y) < 0 || i == n - 1) {
			while ((long long)(toS1.getX() - s1.top().getX()) * (long long)(points[i].getY() - toS1.getY()) -
				(long long)(toS1.getY() - s1.top().getY()) * (long long)(points[i].getX() - toS1.getX()) >= 0) {
				if (s1.size() <= 1) break;
				toS1 = s1.top();
				s1.pop();
			}
			s1.push(toS1);
			toS1 = points[i];
		}
	}
	for (int i = n - 2; i >= 0; --i) {
		if (l(points[i].x, points[i].y) > 0 || i == 0) {
			while ((long long)(toS1.getX() - s1.top().getX()) * (long long)(points[i].getY() - toS1.getY()) -
				(long long)(toS1.getY() - s1.top().getY()) * (long long)(points[i].getX() - toS1.getX()) >= 0) {
				if (s1.size() <= 2) break;
				toS1 = s1.top();
				s1.pop();
			}
				s1.push(toS1);
				toS1 = points[i];
		}
	}
	n = s1.size() - 1;
	delete[] points;
	points = new Point[n];
	//std::cout << n << std::endl;
	for (int i = 0; i < n; ++i) {
		points[i] = s1.top();
		//std::cout << s1.top() << std::endl;
		s1.pop();
	}
}

void Polygon::square() {
	int & n = numOfPoints;
	long long s = 0;
	for (int i = 0; i < numOfPoints - 1; ++i) s += (long long)(points[i].getX()) * (long long)(points[i + 1].getY()) -
		(long long)(points[i].getY()) * (long long)(points[i + 1].getX());
	s += (long long)(points[n - 1].getX()) * (long long)(points[0].getY()) -
		(long long)(points[n - 1].getY()) * (long long)(points[0].getX());
	if (s < 0) s *= -1;
	std::cout << s / 2;
	if (s % 2 == 1) std::cout << ".5";
}

void Polygon::shift(const Vector & a){
	for (int i = 0; i < numOfPoints; ++i) (*(points + i)).shift(a);
}

bool Polygon::contain(const Point & a){
	for (int i = 0; i < numOfPoints - 1; ++i)
		if (Segment(*(points + i), *(points + i + 1)).contain(a)) return true;
	if (Segment(*(points + numOfPoints - 1), *(points)).contain(a)) return true;
	Ray r(a, Point(a.x + 5, a.y + 10000007));
	bool inPolygon = false;
	for (int i = 0; i < numOfPoints - 1; ++i)
		if (r.cross(Segment(*(points + i), *(points + i + 1)))) inPolygon = !inPolygon;
	if (r.cross(Segment(*(points + numOfPoints - 1), *(points)))) inPolygon = !inPolygon;
	return inPolygon;
}

bool Polygon::cross(const Segment & a){
	if ((*this).contain(a.A)) return true;
	if ((*this).contain(a.B)) return true;
	if((*this).contain(a.A))
	for (int i = 0; i < numOfPoints - 1; ++i)
		if (Segment(*(points + i), *(points + i + 1)).cross(a)) return true;
	return false;
}