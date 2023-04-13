#pragma once
#include <cmath>
#include <iostream>

class Vec3
{
public:
	Vec3();
	Vec3(double x0, double x1, double x2);

	double x0() const;
	double& x0();
	double x1() const;
	double& x1();
	double x2() const;
	double& x2();

	double cord(size_t dim) const;
	double& cord(size_t dim);

	double operator[](size_t i) const;
	double& operator[](size_t i);

	Vec3 operator-() const;

	Vec3 operator+(const Vec3& v) const;
	Vec3 operator-(const Vec3& v) const;
	Vec3 operator*(const double d) const;
	Vec3 operator/(const double d) const;

	Vec3& operator+=(const Vec3& v);
	Vec3& operator-=(const Vec3& v);
	Vec3& operator*=(const double d);
	Vec3& operator/=(const double d);

	friend std::ostream& operator<< (std::ostream& os, const Vec3& v);

	double length() const;
	double length_squared() const;
private:
	double cord_[3];
};
