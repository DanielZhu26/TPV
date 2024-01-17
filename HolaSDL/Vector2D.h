#ifndef VECTOR2D_H_ // Normalmente lo escriben los IDEs,
#define VECTOR2D_H_ // VS escribe #pragma once
#include "../checkML.h"
#include <iostream>
#include <cmath>

template <typename T>
class Vector2D {
private:
	T x;
	T y;
public:
	
	Vector2D() : x(), y() {}
	
	Vector2D(T x, T y) : x(x), y(y) {}

	T getX() const {
		return x;
	}

	T getY() const {
		return y;
	}

	// normalizar
	void normalize() {
		T magnitud = sqrt(pow(x, 2) + pow(y, 2));
		if (magnitud > 0.0) {
			x = x / magnitud;
			y = y / magnitud;
		}
	}

	// suma
	Vector2D<T> operator+(const Vector2D& v) const {
		Vector2D r;
		r.x = this->x + v.x; 
		r.y = this->y + v.y; 
		return r;
	}
	
	// resta
	Vector2D<T> operator-(const Vector2D& v) const {
		Vector2D r;
		r.x = this->x - v.x; 
		r.y = this->y - v.y;
		return r;
	}

	// producto escalar
	Vector2D<T> operator*(T d) const {
		Vector2D<T> r;
		r.x = x * d;
		r.y = y * d;
		return r;
	}

	// producto vectorial
	T operator*(const Vector2D<T>& d) const {
		return d.x * x + d.y * y;
	}

	std::ostream& operator<<(std::ostream& os) {
		os << "(" << this->getX() << "," << this->getY() << ")";
		return os;
	}
};
template <class T>
using Point2D = Vector2D<T>;
#endif // También lo escriben los IDEs (va con el #ifndef de arriba)



