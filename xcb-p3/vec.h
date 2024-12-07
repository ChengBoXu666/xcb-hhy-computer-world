#ifndef VEC_H
#define VEC_H
#include <cmath>
#define PI acos(-1)

class Vec {
   private:
	double x, y;

   protected:
	void setX(double _x) { x = _x; }
	void setY(double _y) { y = _y; }

   public:
	Vec(double _x, double _y) {
		x = _x;
		y = _y;
	}
	Vec() = default;
	double getX() const { return x; }
	double getY() const { return y; }
	double get_dis() const { return sqrt(x * x + y * y); }
    double get_angle() const { return atan2(y, x); }

	// Overload == operator
	bool operator==(Vec v) const { return (v.x == x && v.y == y); }

	// Example Overloads + operator
	// returns the sum of 2 Vec
	Vec operator+(Vec v) { return Vec(x + v.x, y + v.y); }

	// Overload - on 2 Vectors
	// return their difference Vector
	Vec operator-(Vec v) { return Vec(x - v.x, y - v.y); }

	// Overload * operator on a double k
	// return current Vector scaled by k
	Vec operator*(double k) { return Vec(x * k, y * k); }

    // Overload / operator on a double k
    // return current Vector scaled by 1/k
    Vec operator/(double k) { return Vec(x / k, y / k); }

	// Overload * on  Vectors
	// return thier inner product (scaler product)
	double operator*(Vec v) const { return (x * v.x + y * v.y); }

	// Overload << on an angle
	// return current vector rotated counter clockwise
	// by this angle
	Vec operator<<(double theta) {
		return Vec(x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta));
	}

	// Overload >> on an angle
	// return current vector rotated clockwise
	// by this angle
	Vec operator>>(double theta) {
		return Vec(x * cos(theta) + y * sin(theta), -x * sin(theta) + y * cos(theta));
	}

    // Overload += on a vector
    // add the vector to the current vector
    Vec& operator+=(Vec v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    
    // Overload -= on a vector
    // subtract the vector from the current vector
    Vec& operator-=(Vec v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
};

#endif  // VEC_H