#include "BVHnode.hpp"

bool compareX(shared_ptr<Hittable> obj1, shared_ptr<Hittable> obj2) {
	double max1 = obj1->getAabb().getInterval(1).max;
	double max2 = obj2->getAabb().getInterval(1).max;

	return max1 < max2;
}

bool compareY(shared_ptr<Hittable> obj1, shared_ptr<Hittable> obj2) {
	double max1 = obj1->getAabb().getInterval(2).max;
	double max2 = obj2->getAabb().getInterval(2).max;

	return max1 < max2;
}

bool compareZ(shared_ptr<Hittable> obj1, shared_ptr<Hittable> obj2) {
	double max1 = obj1->getAabb().getInterval(3).max;
	double max2 = obj2->getAabb().getInterval(3).max;

	return max1 < max2;
}

//size_t is an unsigned integer used to represent the size of objects, so it is returned by sizeof()
BVHnode::BVHnode(std::vector<shared_ptr<Hittable>>& objects, size_t start, size_t end, int drawDepth, int parDepth) {
	drawAbabbDepth = drawDepth;
	depth = parDepth;
	m_color = Color(randomDouble(), randomDouble(), randomDouble());
	size_t range = end - start;

	m_aabb = AaBoundingBox();
	for (size_t object_index = start; object_index < end; object_index++)
		m_aabb = AaBoundingBox(m_aabb, objects[object_index]->getAabb());

	int axis = m_aabb.longestAxis();

	auto comparator = (axis == 0) ? compareX
		: (axis == 1) ? compareY
		: compareZ;

	if (range == 1) {
		m_right = m_left = objects[start];
	}
	else if (range == 2) {
		m_right = objects[start];
		m_left = objects[start + 1];
	}
	else {
		std::sort(std::begin(objects) + start, std::begin(objects) + end, comparator);

		auto mid = start + range / 2;
		shared_ptr<BVHnode> left = make_shared<BVHnode>(objects, start, mid, drawAbabbDepth, depth+1);
		shared_ptr<BVHnode> right = make_shared<BVHnode>(objects, mid, end, drawAbabbDepth, depth+1);
		m_left = left;
		m_right = right;
	}
}

bool BVHnode::hit(const Ray& r, Interval interval, HitRecord& rec) const {
	if (!m_aabb.hit(r, interval)) { return false; }

	if (depth == drawAbabbDepth) {
		rec.mat = std::make_shared<Diffuse>(Diffuse(m_color));
		return true;
	}

	bool hit_left = m_left->hit(r, interval, rec);
	bool hit_right = m_right->hit(r, Interval(interval.min, hit_left ? rec.t : interval.max), rec);

	return hit_left || hit_right;
}