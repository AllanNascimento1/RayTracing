#include "Sphere.hpp"

using namespace MyRT;

Sphere::Sphere() 
    : m_center(Point3(0.0, 0.0, 0.0)), 
    m_radius(1.0), 
    m_material(std::make_shared<Material>(Material())),
    m_aabb(Point3(0.0), Point3(0.0)) {}

Sphere::Sphere(const Point3 center, const double radious, const shared_ptr<Material> material)
    : m_center(center), 
    m_radius(radious), 
    m_material(material){
        Point3 vert1 = m_center + Vec3(m_radius);
        Point3 vert2 = m_center - Vec3(m_radius);
        m_aabb = AaBoundingBox(vert1, vert2);
}

bool Sphere::hit(const Ray& r, Interval interval, HitRecord& rec) const {

    /**/
    Vec3 oc = m_center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - m_radius * m_radius;
    /**/

    auto discriminant = h * h - a * c;
    if (discriminant < 0)
        return false;

    auto sqrtd = std::sqrt(discriminant);

    auto root = (h - sqrtd) / a;
    
    if (!interval.surrounds(root)) {
        root = (h + sqrtd) / a;
        if (!interval.surrounds(root))
            return false;
    }

    rec.mat = m_material;
    rec.t = root;
    rec.p = r.at(root);
    Vec3 normal = (r.at(root) - m_center) / m_radius;
    rec.setFaceNormal(r, unit_vector(normal));

    return true;
}