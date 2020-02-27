#pragma once

#include "headers.h"

class Vector3D {
public:
	Vector3D(double x, double y, double z): x(x), y(y), z(z) {}
	Vector3D() {}
	double x, y, z;

	void operator+=(Vector3D a) {
		x += a.x;
		y += a.y;
		z += a.z;
	}
	void operator-=(Vector3D a) {
		x -= a.x;
		y -= a.y;
		z -= a.z;
	}
};

Vector3D operator+ (Vector3D a, Vector3D b) {
	return Vector3D(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3D operator- (Vector3D a, Vector3D b) {
	return Vector3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3D operator* (Vector3D a, double b) {
	return Vector3D(a.x * b, a.y * b, a.z * b);
}

Vector3D operator* (double b, Vector3D a) {
	return Vector3D(a.x * b, a.y * b, a.z * b);
}

Vector3D operator/ (Vector3D a, double b) {
	return Vector3D(a.x / b, a.y / b, a.z / b);
}

double operator* (Vector3D a, Vector3D b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

double operator/ (Vector3D a, Vector3D b) {
	return (a * b) / (b * b);
}

double abs2(Vector3D x) {
	return x * x;
}

double abs(Vector3D x) {
	return sqrt(x * x);
}

Vector3D operator%(Vector3D a, Vector3D b) {
	return Vector3D(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

std::ostream& operator<<(std::ostream& out, Vector3D x) {
	out << x.x << " " << x.y << " " << x.z;
	return out;
}

Vector3D v_rand() {
	return Vector3D(rand(), rand(), rand()) / RAND_MAX;
}