#include "Sphere.hpp"

MyRT::Sphere::Sphere() : m_center(Point3(0.0, 0.0, 0.0)), m_radius(1.0) {}

MyRT::Sphere::Sphere(const Point3 center, const double radious) : m_center(center), m_radius(radious) {}

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

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - m_center) / m_radius;

    return true;
}