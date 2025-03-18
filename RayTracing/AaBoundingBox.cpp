#include "AaBoundingBox.hpp";

AaBoundingBox::AaBoundingBox(Point3 vert1, Point3 vert2) {
	m_x = (vert1.x() > vert2.x())? Interval(vert2.x(), vert1.x()) : Interval(vert1.x(), vert2.x());
	m_y = (vert1.y() > vert2.y())? Interval(vert2.y(), vert1.y()) : Interval(vert1.y(), vert2.y());
	m_z = (vert1.z() > vert2.z())? Interval(vert2.z(), vert1.z()) : Interval(vert1.z(), vert2.z());
}

AaBoundingBox::AaBoundingBox(AaBoundingBox box1, AaBoundingBox box2) {
	m_x = Interval(box1.m_x, box2.m_x);
	m_y = Interval(box1.m_y, box2.m_y);
	m_z = Interval(box1.m_z, box2.m_z);
}

Interval AaBoundingBox::getInterval(int n) const {
	switch (n) {
		case 1:
			return m_y;
		case 2:
			return m_z;
		default:
			return m_x;
	}
}

bool AaBoundingBox::hit(const Ray& ray, Interval baseInter) const {
	Point3 orig = ray.origin();
	Vec3 dir = ray.direction();
	for (int i = 0; i < 3; i++) {
		Interval p = getInterval(i);
		double tempDir = 1 / dir[i];
		double t1 = (p.min - orig[i]) * tempDir;
		double t2 = (p.max - orig[i]) * tempDir;

		if (t1 < t2) {
			if (t1 > baseInter.min) { baseInter.min = t1; }
			if (t2 < baseInter.max) { baseInter.max = t2; }
		}else{
			if (t2 > baseInter.min) { baseInter.min = t2; }
			if (t1 < baseInter.max) { baseInter.max = t1; }
		}

		if (baseInter.min >= baseInter.max) {
			return false;
		}
	}
	return true;
}