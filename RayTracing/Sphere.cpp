#include "Sphere.hpp"

MyRT::Sphere::Sphere() 
    : m_center(Point3(0.0, 0.0, 0.0)), 
    m_radius(1.0), 
    m_material(std::make_shared<Material>(Material())) {}

MyRT::Sphere::Sphere(const Point3 center, const double radious, const shared_ptr<Material> material)
    : m_center(center), 
    m_radius(radious), 
    m_material(material){}

bool MyRT::Sphere::hit(const Ray& r, Interval interval, HitRecord& rec) const {
    //Interval interval;
    Vec3 oc = m_center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - m_radius * m_radius;

    auto discriminant = h * h - a * c;
    if (discriminant < 0)
        return false;

    auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (h - sqrtd) / a;
    
    if (!interval.surrounds(root)) {
        root = (h + sqrtd) / a;
        if (!interval.surrounds(root))
            return false;
    }

    //std::cout << root << std::endl;

    rec.mat = m_material;
    rec.t = root;
    rec.p = r.at(root);
    Vec3 normal = (rec.p - m_center) / m_radius;
    rec.setFaceNormal(r, normal);

    return true;
}