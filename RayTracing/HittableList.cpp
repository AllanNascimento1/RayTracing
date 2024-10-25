#include "HittableList.hpp"

bool MyRT::HittableList::hit(const Ray& r, Interval interval, HitRecord& rec) const {
	HitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = interval.max;

	for (const auto& obj : m_objects) {
		if (obj->hit(r, Interval(interval.min, closestSoFar), tempRec)) {
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}