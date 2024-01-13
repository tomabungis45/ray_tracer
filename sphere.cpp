#include "sphere.h"
#include "hittable.h"
#include "vec3.h"

sphere::sphere(const point3 &center, const double &radius)
    : center{center}, radius{radius} {}

bool sphere::hit(const ray &r, const interval &ray_t, hit_record &rec) const {
    auto ac = r.origin() - center;

    auto a = r.direction().length_squared();
    auto half_b = dot(r.direction(), ac);
    auto c = ac.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    auto sqrtd = sqrt(discriminant);

    if (discriminant < 0)
        return false;

    // find smallest t within range (what is the range for???)
    auto root = (-half_b - sqrtd) / a;
    if (!ray_t.surrounds(root)) { // check function for why we do !surrounds!!
        root = (-half_b + sqrtd) / a;
        if (!ray_t.surrounds(root))
            return false;
    }

    rec.t = root;
    rec.p = r.at(root);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    return true;
}