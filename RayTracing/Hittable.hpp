#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "Ray.hpp"

namespace MyRT {

    class HitRecord {
        public:
            double t;
            Point3 p;
            Vec3 normal;
            bool isOutside;

            void setFaceNormal(const Ray& r, const Vec3& p_normal) {
                isOutside = dot(r.direction(), normal) < 0.0;
                normal = (isOutside)? p_normal : -p_normal;
            }
    };

    class Hittable {
        public:
            virtual ~Hittable() = default;

            virtual bool hit(const Ray& r, Interval interval, HitRecord& rec) const = 0;
    };

}

#endif // !HITTABLE_HPP
