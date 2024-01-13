#ifndef COLOR_H
#define COLOR_H
#include "interval.h"
#include "vec3.h"

using color = vec3;

inline void write_color(std::ostream &out, color pixel_color,
                        int samples_per_pixel) {
    // write the color in [0,255] format

    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // divide summed up color with samples_per_pixel
    double scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    static const interval intensity(0.000, 0.999);

    out << static_cast<int>(256 * intensity.clamp(r))
        << ' ' // why 256 and not 255.999???
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

#endif