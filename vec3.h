#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
    double e[3];

  public:
    vec3();
    vec3(const double &, const double &, const double &);

    double x() const;
    double y() const;
    double z() const;

    double operator[](const int &i) const; // when we wanna get a value
    double &operator[](
        const int &); // when we want to change a value, hence the reference

    vec3 operator-() const;
    vec3 operator+=(const vec3 &);
    vec3 operator*=(const double &);
    vec3 operator/=(const double &);

    double length() const;
    double length_squared() const;

    // friend utility functions functions
    static vec3 random();
    static vec3 random(const double &min, const double &max);
    static vec3 random_in_unit_sphere();
    static vec3 random_unit_vector();
    static vec3 random_on_hemisphere(const vec3 &normal);

    friend std::ostream &operator<<(std::ostream &, const vec3 &v);
    friend vec3 operator+(const vec3 &, const vec3 &);
    friend vec3 operator-(const vec3 &, const vec3 &);
    friend vec3 operator*(const vec3 &, const vec3 &);
    friend vec3 operator*(const double &, const vec3 &);
    friend vec3 operator*(const vec3 &, const double &);
    friend vec3 operator/(const vec3 &, const double &);
    friend double dot(const vec3 &, const vec3 &);
    friend vec3 cross(const vec3 &, const vec3 &);
    friend vec3 unit_vector(const vec3 &v);
};

using point3 = vec3;

#endif
