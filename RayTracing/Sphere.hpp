#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "RTutility.hpp"
#include "Hittable.hpp"
#include "Material.hpp"

namespace MyRT {

	class Sphere : public Hittable{
		public:
			Sphere();
			Sphere(const Point3 center, const double radious, const shared_ptr<Material> material);

			bool hit(const Ray& r, Interval interval, HitRecord& rec) const override;

		private:
			Point3 m_center;
			double m_radius;
			shared_ptr<Material> m_material;
	};

}

#endif // !SPHERE_HPP
