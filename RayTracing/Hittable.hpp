#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "Ray.hpp"

namespace MyRT {
    class HitRecord {
    public:
        Point3 p;
        Vec3 normal;
        double t;
    };

    class Hittable {
    public:
        virtual ~Hittable() = default;

        virtual bool hit(const Ray& r, Interval interval, HitRecord& rec) const = 0;
    };

}

#endif // !HITTABLE_HPP
