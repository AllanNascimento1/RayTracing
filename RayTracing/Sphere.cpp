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

    Vec3 matrixVecX = Vec3(1.0, 0.0, 0.0);
    Vec3 matrixVecY = Vec3(0.0, 1.0, 0.0);
    Vec3 matrixVecZ = Vec3(0.0, 0.0, 1.0);

    Vec3 tempDir = (r.direction() * matrixVecX) + (r.direction() * matrixVecY) + (r.direction() * matrixVecZ);
    Point3 tempOrig = (r.origin() * matrixVecX) + (r.origin() * matrixVecY) + (r.origin() * matrixVecZ);
    Ray tempRay= Ray(tempOrig, tempDir);

    Vec3 oc = m_center - tempOrig;
    auto a = tempDir.length_squared();
    auto h = dot(tempDir, oc);
    auto c = oc.length_squared() - m_radius * m_radius;
    
    /*
    Vec3 oc = m_center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - m_radius * m_radius;
    /**/

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
    rec.p = tempRay.at(root);
    Vec3 normal = (rec.p - m_center) / m_radius;
    normal = (normal * matrixVecX) + (normal * matrixVecY) + (normal * matrixVecZ);
    rec.setFaceNormal(r, unit_vector(normal));

    return true;
}