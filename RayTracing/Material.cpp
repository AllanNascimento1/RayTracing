#include "Material.hpp"
#include "Hittable.hpp"

bool MyRT::Lambertian::scatter(const Ray& rayIn, const HitRecord& rec, Color& att, Ray& rayOut) const {
    att = Color(0.0, 0.0, 0.0);
    if (rec.isOutside) {
        att = m_albedo;
        rayOut = Ray(rec.p, rec.normal + Vec3::randomUnitVec());
    }
    return rec.isOutside;
}

Color MyRT::Diffuse::emitted() const {
    return m_albedo;
}