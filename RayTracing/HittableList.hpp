#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include <memory>
#include <vector>

#include "Hittable.hpp"
#include "Interval.hpp"

using std::make_shared;
using std::shared_ptr;

namespace MyRT {
    
    class HittableList : public Hittable {
        public:
            std::vector<shared_ptr<Hittable>> m_objects;

            HittableList() {}
            HittableList(shared_ptr<Hittable> object) { add(object); }

            void add(shared_ptr<Hittable> obj) {
                m_objects.push_back(obj);
            }

            bool hit(const Ray& r, Interval interval, HitRecord& rec) const override;

    };

}

#endif // HITTABLE_LIST
