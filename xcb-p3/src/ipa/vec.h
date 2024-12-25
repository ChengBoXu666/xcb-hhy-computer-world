#ifndef VEC_H
#define VEC_H
#include <cmath>
#include <vector>
#define PI (float)acos(-1)

class Vec {
   private:
	float x, y;

   public:
	Vec(float _x, float _y) : x(_x),y(_y){}
	Vec() : x(0), y(0) {}
	~Vec() {}
	float getX() const { return x; }
	float getY() const { return y; }
	float get_dis() const { return (float)sqrt(x * x + y * y); }
    float get_angle() const { return (float)atan2(y, x); }

	// Overload == operator
	bool operator==(Vec v) const { return (v.x == x && v.y == y); }

	// Example Overloads + operator
	// returns the sum of 2 Vec
	Vec operator+(Vec v) { return Vec(x + v.x, y + v.y); }

	// Overload - on 2 Vectors
	// return their difference Vector
	Vec operator-(Vec v) const { return Vec(x - v.x, y - v.y); }

	// Overload * operator on a float k
	// return current Vector scaled by k
	Vec operator*(float k) const { return Vec(x * k, y * k); }

    // Overload / operator on a float k
    // return current Vector scaled by 1/k
    Vec operator/(float k) const { return Vec(x / k, y / k); }

	// Overload * on  Vectors
	// return thier inner product (scaler product)
	float operator*(Vec v) const { return (x * v.x + y * v.y); }

	// Overload << on an angle
	// return current vector rotated counter clockwise
	// by this angle
	Vec operator<<(float theta) {
		return Vec((float)(x * cos(theta) - y * sin(theta)), (float)(x * sin(theta) + y * cos(theta)));
	}

	// Overload >> on an angle
	// return current vector rotated clockwise
	// by this angle
	Vec operator>>(float theta) {
		return Vec((float)(x * cos(theta) + y * sin(theta)), (float)(-x * sin(theta) + y * cos(theta)));
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

	static Vec bezier(const Vec& p0, const Vec& p1, const Vec& p2, float t) {
        return (p0 *((1 - t) * (1 - t))) + (p1 * 2 * (1 - t) * t) + (p2 * t * t);
    }

	static Vec bezier(const std::vector<Vec>& points, float t) {
        if (points.size() == 1) {
            return points[0];
        }
        std::vector<Vec> newPoints;
        for (size_t i = 0; i < points.size() - 1; ++i) {
            newPoints.push_back(points[i] * (1 - t) + points[i + 1] * t);
        }
        return bezier(newPoints, t);
    }
};

#endif // VEC_H