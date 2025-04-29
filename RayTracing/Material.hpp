#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Ray.hpp"

namespace MyRT {

	class HitRecord;

	class Material {
		public:
			Material() {}

			virtual ~Material() = default;

			virtual Color emitted() const {
				return Color(0, 0, 0);
			}

			virtual bool scatter(const Ray& rayIn, const HitRecord& rec, Color& att, Ray& rayOut) const { 
				return false; 
			}
	};
	
	class Lambertian : public Material{
		public:

			Lambertian(const Color& albedo) : m_albedo(albedo) {}

			bool scatter(const Ray& rayIn, const HitRecord& rec, Color& att, Ray& rayOut) const override;

		private:

			Color m_albedo;

	};

	class Diffuse : public Material {
		public:

			Diffuse(const Color& albedo) : m_albedo(albedo) {}

			bool scatter(const Ray& rayIn, const HitRecord& rec, Color& att, Ray& rayOut) const { return false; }

			Color emitted() const;

		private:

			Color m_albedo;

	};
		
}

#endif