#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Hittable.hpp"

namespace MyRT {

	class Material {
		public:
			virtual ~Material() = default;

			virtual bool scatter(const Ray& rayIn, const Color& att, const HitRecord& rec, Ray& rayOut) const {
				return false;
			};
	};

	class Lambertian : public Material{
		public:

			Lambertian();
			Lambertian(const Color& albedo) : m_albedo(albedo) {}

			bool scatter(const Ray& rayIn, const Color& att, const HitRecord& rec, Ray& rayOut) const override;

		private:

			Color m_albedo;

	};
}

#endif