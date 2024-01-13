#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "interval.h"
#include "vec3.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
  public:
    std::vector<shared_ptr<hittable>> objects;
    hittable_list();
    hittable_list(shared_ptr<hittable>);
    void clear();
    void add(shared_ptr<hittable>);
    bool hit(const ray &r, const interval &ray_T,
             hit_record &rec) const override;
};

#endif