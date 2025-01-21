#ifndef RAY_H
#define RAY_H

#include "RTutility.hpp"

namespace MyRT {

	class Ray {
		public:
			Ray() : m_orig(Point3(0.0, 0.0, 0.0)), m_dir(Vec3(0.0, 0.0, 0.0)) {}

			Ray(const Point3 orig, const Vec3 dir) : m_orig(orig), m_dir(dir) {}

			Vec3 at(double t) const { return m_orig + (m_dir * t); }

			Point3 origin() const { return m_orig; }
			Vec3 direction() const { return m_dir; }

		private:
			Point3 m_orig;
			Vec3 m_dir;

	};

}

#endif // !RAY_H
