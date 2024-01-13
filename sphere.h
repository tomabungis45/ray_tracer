#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "interval.h"
#include "vec3.h"

class sphere : public hittable {
  private:
    point3 center;
    double radius;

  public:
    sphere(const point3 &, const double &);

    bool hit(const ray &r, const interval &ray_t,
             hit_record &rec) const override;
};

#endif