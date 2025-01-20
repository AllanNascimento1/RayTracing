#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Interval.hpp"
#include "Hittable.hpp"
#include "Ray.hpp"

namespace MyRT
{
	class Square : public Hittable{
		public:
			Square(const shared_ptr<Material> material)
				: m_orig(-0.5, 0.5, 0.0), 
				m_wVec(1.0, 0.0, 0.0), 
				m_wLenght(1.0), 
				m_hVec(0.0, -1.0, 0.0), 
				m_hLenght(1.0),
				m_material(material) {};

			bool hit(const Ray& r, Interval interval, HitRecord& rec) const override;

		private:
			Point3 m_orig;
			Vec3 m_wVec;
			double m_wLenght;
			Vec3 m_hVec;
			double m_hLenght;
			shared_ptr<Material> m_material;
	};
}
#endif
