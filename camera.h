#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

#include "color.h"
#include "hittable.h"

class camera {
  public:
    double aspect_ratio = 1.0; // ratio between width and height
    int image_width = 100;     // columns
    int samples_per_pixel = 10;
    int max_depth = 10;
    void render(const hittable &world);

  private:
    int image_height;   // rendered image height
    point3 center;      // camera center
    point3 pixel00_loc; // location of pixel 0,0
    vec3 pixel_delta_u; // offset row vp image
    vec3 pixel_delta_v; // offset column vp image

    void initialize();
    color ray_color(const ray &r, int depth, const hittable &world);
    ray get_ray(const int &i, const int &j) const;
    vec3 pixel_sample_square() const;
};

#endif