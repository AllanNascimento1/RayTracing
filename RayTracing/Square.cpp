#include "Square.hpp"

bool MyRT::Square::hit(const Ray& r, Interval interval, HitRecord& rec) const {
	Vec3 oc = m_orig - r.origin();
	double root = oc.z() / r.direction().z();
	Vec3 tempPoint = root * r.direction();

	if (!interval.surrounds(root)) {
		return false;
	}

	if (tempPoint.x() >= oc.x() && tempPoint.x() <= (oc.x() + m_wVec.x()) ) {
		if (tempPoint.y() >= oc.y() + m_hVec.y() && tempPoint.y() <= oc.y() ) {
			rec.normal = Vec3(0.5, 0.0, 1.0);
			rec.t = root;
			rec.p = tempPoint;
			rec.mat = m_material;
			return true;
		}
	}

	return false;
}