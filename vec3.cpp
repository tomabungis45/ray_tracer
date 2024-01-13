#include "vec3.h"
#include "rtweekend.h"
#include <iostream>

vec3::vec3() : e{0, 0, 0} {}
vec3::vec3(const double &e1, const double &e2, const double &e3)
    : e{e1, e2, e3} {}

double vec3::x() const { return e[0]; }
double vec3::y() const { return e[1]; }
double vec3::z() const { return e[2]; }

double vec3::operator[](const int &i) const { return e[i]; }
double &vec3::operator[](const int &i) { return e[i]; }

vec3 vec3::operator-() const { return vec3{-e[0], -e[1], -e[2]}; }

vec3 vec3::operator+=(const vec3 &v) {
    e[0] += v[0];
    e[1] += v[1];
    e[2] += v[2];
    return *this;
}

vec3 vec3::operator*=(const double &t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

vec3 vec3::operator/=(const double &t) { return (*this) *= (1 / t); }

double vec3::length() const { return sqrt(length_squared()); }

double vec3::length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

// FRIEND FUNCTIONS!!!!!!!!!

std::ostream &operator<<(std::ostream &o, const vec3 &v) {
    return o << v[0] << ' ' << v[1] << ' ' << v[2];
}

vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3{u[0] + v[0], u[1] + v[1], u[2] + v[2]};
}

vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3{u[0] - v[0], u[1] - v[1], u[2] - v[2]};
}

vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3{u[0] * v[0], u[1] * v[1], u[2] * v[2]};
}

vec3 operator*(const vec3 &u, const double &t) {
    return vec3{t * u[0], t * u[1], t * u[2]};
}

vec3 operator*(const double &t, const vec3 &u) { return u * t; }

vec3 operator/(const vec3 &u, const double &t) { return u * (1 / t); }

double dot(const vec3 &u, const vec3 &v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}
// look into definiton, fomrula 3b1b
vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3{u[1] * v[2] - u[2] * v[1], u[2] * v[0] - v[0] * u[2],
                u[0] * v[1] - v[1] * u[0]};
}

vec3 unit_vector(const vec3 &v) { return v / v.length(); }

vec3 vec3::random() {
    return vec3(random_double(), random_double(), random_double());
}

vec3 vec3::random(const double &min, const double &max) {
    return vec3(random_double(min, max), random_double(min, max),
                random_double(min, max));
}

vec3 vec3::random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() < 1)
            return p;
    }
}

vec3 vec3::random_unit_vector() { return unit_vector(random_in_unit_sphere()); }

vec3 vec3::random_on_hemisphere(const vec3 &normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) >
        0) { // when dot prod is>0 we have the same hemisphere
        return on_unit_sphere;
    } else {
        return -on_unit_sphere;
    }
}