#ifndef AABOUNDINGBOX_HPP
#define AABOUNDINGBOX_HPP

#include "Interval.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"

using namespace MyRT;

class AaBoundingBox{
	public:
		AaBoundingBox() : m_x(Interval()), m_y(Interval()), m_z(Interval()) {}
		AaBoundingBox(Point3 vert1, Point3 vert2);
		AaBoundingBox(Interval x, Interval y, Interval z) : m_x(x), m_y(y), m_z(z) {};
		AaBoundingBox(AaBoundingBox box1, AaBoundingBox box2);

		bool hit(const Ray& ray, Interval baseInter) const;

		Interval getInterval(int n) const;

		int longestAxis() const {
			if (m_x.size() > m_y.size()) {
				return m_x.size() > m_z.size() ? 0 : 2;
			}else {
				return m_y.size() > m_z.size() ? 1 : 2;
			}
		}

	private:
		Interval m_x;
		Interval m_y;
		Interval m_z;

};

#endif