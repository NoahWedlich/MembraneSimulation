#include "Vec3.h"

Vec3::Vec3()
    : cord_{0, 0, 0}
{}

Vec3::Vec3(double x0, double x1, double x2)
    : cord_{x0, x1, x2}
{}

double Vec3::x0() const
{ return cord_[0]; }

double& Vec3::x0()
{ return cord_[0]; }

double Vec3::x1() const
{ return cord_[1]; }

double& Vec3::x1()
{ return cord_[1]; }

double Vec3::x2() const
{ return cord_[2]; }

double& Vec3::x2()
{ return cord_[2]; }

double Vec3::cord(size_t dim) const
{ return cord_[dim]; }

double& Vec3::cord(size_t dim)
{ return cord_[dim]; }

double Vec3::operator[](size_t i) const
{ return cord_[i]; }

double& Vec3::operator[](size_t i)
{ return cord_[i]; }

Vec3 Vec3::operator-() const
{
    return Vec3(
        -cord_[0],
        -cord_[1],
        -cord_[2]
    );
}

Vec3 Vec3::operator+(const Vec3& v) const
{
    return Vec3(
        cord_[0] + v.cord_[0],
        cord_[1] + v.cord_[1],
        cord_[2] + v.cord_[2]
    );
}

Vec3 Vec3::operator-(const Vec3& v) const
{
    return Vec3(
        cord_[0] - v.cord_[0],
        cord_[1] - v.cord_[1],
        cord_[2] - v.cord_[2]
    );
}

Vec3 Vec3::operator*(const Vec3& v) const
{
    return Vec3(
        cord_[0] * v.cord_[0],
        cord_[1] * v.cord_[1],
        cord_[2] * v.cord_[2]
    );
}

Vec3 Vec3::operator/(const Vec3& v) const
{
    return Vec3(
        cord_[0] / v.cord_[0],
        cord_[1] / v.cord_[1],
        cord_[2] / v.cord_[2]
    );
}

Vec3 Vec3::operator+(const double d) const
{
    return Vec3(
        cord_[0] + d,
        cord_[1] + d,
        cord_[2] + d
    );
}

Vec3 Vec3::operator-(const double d) const
{
    return Vec3(
        cord_[0] - d,
        cord_[1] - d,
        cord_[2] - d
    );
}

Vec3 Vec3::operator*(const double d) const
{
    return Vec3(
        cord_[0] * d,
        cord_[1] * d,
        cord_[2] * d
    );
}

Vec3 Vec3::operator/(const double d) const
{
    return Vec3(
        cord_[0] / d,
        cord_[1] / d,
        cord_[2] / d
    );
}

Vec3& Vec3::operator+=(const Vec3& v)
{
    cord_[0] += v.cord_[0];
    cord_[1] += v.cord_[1];
    cord_[2] += v.cord_[2];
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& v)
{
    cord_[0] -= v.cord_[0];
    cord_[1] -= v.cord_[1];
    cord_[2] -= v.cord_[2];
    return *this;
}

Vec3& Vec3::operator*=(const Vec3& v)
{
    cord_[0] *= v.cord_[0];
    cord_[1] *= v.cord_[1];
    cord_[2] *= v.cord_[2];
    return *this;
}

Vec3& Vec3::operator/=(const Vec3& v)
{
    cord_[0] /= v.cord_[0];
    cord_[1] /= v.cord_[1];
    cord_[2] /= v.cord_[2];
    return *this;
}

Vec3& Vec3::operator+=(const double d)
{
    cord_[0] += d;
    cord_[1] += d;
    cord_[2] += d;
    return *this;
}

Vec3& Vec3::operator-=(const double d)
{
    cord_[0] -= d;
    cord_[1] -= d;
    cord_[2] -= d;
    return *this;
}

Vec3& Vec3::operator*=(const double d)
{
    cord_[0] *= d;
    cord_[1] *= d;
    cord_[2] *= d;
    return *this;
}

Vec3& Vec3::operator/=(const double d)
{
    cord_[0] /= d;
    cord_[1] /= d;
    cord_[2] /= d;
    return *this;
}

double Vec3::dot(const Vec3& other)
{
    return cord_[0]*other.cord_[0] + cord_[1]*other.cord_[1] + cord_[2]*other.cord_[2];
}

double Vec3::angle(const Vec3& other)
{
    return std::acos(dot(other) / (length()*other.length()));
}

double Vec3::length() const
{
    return std::sqrt( cord_[0]*cord_[0] +
                      cord_[1]*cord_[1] +
                      cord_[2]*cord_[2] );
}

double Vec3::length_squared() const
{
    return cord_[0] * cord_[0] +
           cord_[1] * cord_[1] +
           cord_[2] * cord_[2];
}

std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
    os << "Vec3( " << v.cord_[0] << " | " << v.cord_[1] << " | " << v.cord_[2] << " )";
    return os;
}
