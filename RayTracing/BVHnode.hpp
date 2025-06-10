#ifndef BVHNODE_HPP
#define BVHNODE_HPP

#include "AaBoundingBox.hpp"
#include "Hittable.hpp"

#include <algorithm>

class BVHnode : public Hittable{
	public:
		BVHnode(HittableList list) : BVHnode(list.m_objects, 0, list.m_objects.size()) {}
		BVHnode(HittableList list, int drawDepth) : BVHnode(list.m_objects, 0, list.m_objects.size(), drawDepth, 0) {}

		BVHnode(std::vector<shared_ptr<Hittable>>& objects, size_t start, size_t end) : BVHnode(objects, start, end, -1, 0) {};
		BVHnode(std::vector<shared_ptr<Hittable>>& objects, size_t start, size_t end, int drawDepth, int parDepth);

		bool hit(const Ray& r, Interval interval, HitRecord& rec) const override;

		AaBoundingBox getAabb() const override{
			return m_aabb;
		}

		void setDrawDepth(int depth) {
			drawAbabbDepth = depth;
		}

		void setDepth(int parDepth) {
			depth = parDepth;
		}

		int depth;
		int drawAbabbDepth;

	private:
		shared_ptr<Hittable> m_left;
		shared_ptr<Hittable> m_right;
		AaBoundingBox m_aabb;
		Color m_color;
};

#endif