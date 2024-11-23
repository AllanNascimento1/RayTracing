#include "Material.hpp";
#include "Hittable.hpp";

bool MyRT::Material::scatter(const Ray& rayIn, const HitRecord& rec, Color& att, Ray& rayOut) const {
	att = Color( (rec.normal+Vec3(1.0 , 1.0 , 1.0)) / 2.0 );

	return false;	
}

bool MyRT::Lambertian::scatter(const Ray& rayIn, const HitRecord& rec, Color& att, Ray& rayOut) const {
	att = m_albedo;
	rayOut = Ray( rec.p , rec.normal + randomUnitVec());
	return true;
}
