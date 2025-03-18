#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include <memory>
#include <vector>

#include "RTutility.hpp"
#include "Ray.hpp"
#include "Material.hpp"
#include "AaBoundingBox.hpp"

using std::make_shared;
using std::shared_ptr;

namespace MyRT {

    class HitRecord {
        public:
            double t;
            Point3 p;
            Vec3 normal;
            shared_ptr<Material> mat;
            bool emmited;
            bool isOutside;

            void setFaceNormal(const Ray& r, const Vec3& p_normal) {
                isOutside = dot(r.direction(), p_normal) < 0.0;
                normal = (isOutside)? p_normal : -p_normal;
            }
    };

    class Hittable {
        public:
            virtual ~Hittable() = default;

            virtual bool hit(const Ray& r, Interval interval, HitRecord& rec) const = 0;

            virtual AaBoundingBox getAabb() const = 0;
    };

    class HittableList : public Hittable {
        public:
            std::vector<shared_ptr<Hittable>> m_objects;

            HittableList() {}
            HittableList(shared_ptr<Hittable> object) { add(object); }

            void add(shared_ptr<Hittable> obj) {
                m_objects.push_back(obj);
            }

            bool hit(const Ray& r, Interval interval, HitRecord& rec) const override;

            AaBoundingBox getAabb() const override { return m_aabb;  }

        private:
            AaBoundingBox m_aabb;
    };

}

#endif // !HITTABLE_HPP
