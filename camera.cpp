#include "camera.h"
#include "color.h"
#include "rtweekend.h"

#include <iostream>
#include <utility>

void camera::render(const hittable &world) {
    initialize();

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' '
                  << std::flush;
        for (int i = 0; i < image_width; i++) {
            color pixel_color{0, 0, 0};

            for (int sample = 0; sample < samples_per_pixel; sample++) {
                ray r = get_ray(i, j);
                pixel_color += ray_color(r, max_depth, world);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::clog << "\rDone.                           \n";
}

void camera::initialize() {
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    center = point3{0, 0, 0};

    // viewport dimensions;
    double focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width =
        viewport_height * (static_cast<double>(image_width) / image_height);

    // claculating the vectors of horizontal and vertical edges
    auto viewport_u = vec3{viewport_width, 0, 0};
    auto viewport_v =
        vec3{0, -viewport_height, 0}; // negative because in image matrix
    // goes from up to down

    // Calculate the delta vectors
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // calculate upper left corner
    auto viewport_upper_left =
        center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;

    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

color camera::ray_color(const ray &r, int depth, const hittable &world) {
    hit_record rec;
    if (depth <= 0)
        return color{0, 0, 0};

    if (world.hit(r, interval(0.001, inf), rec)) {
        vec3 direction = rec.normal + vec3::random_unit_vector();
        return 0.5 * ray_color(ray(rec.p, direction), depth - 1, world);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

ray camera::get_ray(const int &i, const int &j) const {
    point3 pixel_center =
        pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    auto pixel_sample = pixel_center + pixel_sample_square();

    auto ray_origin = center;
    auto ray_dir = pixel_sample - ray_origin;

    return ray{ray_origin, ray_dir};
}

vec3 camera::pixel_sample_square() const {
    // shift range from 0 to 1 to -0.5 to 0.5
    auto px = -0.5 + random_double();
    auto py = -0.5 + random_double();
    return (px * pixel_delta_u) + (py * pixel_delta_v);
}