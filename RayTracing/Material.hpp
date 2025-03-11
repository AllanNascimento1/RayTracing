#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Ray.hpp"

namespace MyRT {

	class HitRecord;

	class Material {
		public:
			Material() {}

			virtual ~Material() = default;

			virtual Color emitted(double u, double v, const Point3& p) const {
				return Color(0, 0, 0);
			}

			virtual bool scatter(const Ray& rayIn, const HitRecord& rec, Color& att, Ray& rayOut) const;
	};
	
	class Lambertian : public Material{
		public:

			Lambertian();
			Lambertian(const Color& albedo) : m_albedo(albedo) {}

			bool scatter(const Ray& rayIn, const HitRecord& rec, Color& att, Ray& rayOut) const override;

		private:

			Color m_albedo;

	};
		
}

#endif