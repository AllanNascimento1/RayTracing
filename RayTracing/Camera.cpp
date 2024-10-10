#include "Camera.hpp"
#include <iostream>

MyRT::Camera::Camera(int screenWidth, int screenHeight)
    : m_orig(0.0, 0.0, 0.0),
    m_lookAt(0.0, 0.0, 1.0),
    m_up(0.0, 1.0, 0.0),
    m_focusDistance(1.0),
    m_defocusAngle(1.0),
    m_fovAngle(90.0),
    m_numberSamples(10),
    m_imageHeight(screenHeight),
    m_imageWidth(screenWidth),
    m_aspectRatio(static_cast<double>(screenWidth) / screenHeight) {}

MyRT::Camera::Camera() : Camera(600, 960) {}

void MyRT::Camera::render(Image &outImage, const Hittable& obj) const{
    for (int y = 0; y < m_imageHeight; y++) {
        for (int x = 0; x < m_imageWidth; x++) {
            Vec3 direction = (m_pixel00 - m_orig) + (m_pixelDeltaW * x) - (m_pixelDeltaH * y);
            Ray ray = Ray(m_orig, direction);

            HitRecord rec = HitRecord();

            Color color;

            //std::cout << obj.m_radius << std::endl;
            if (obj.hit(ray, Interval(0.0, RT_INFINITY), rec)) {
                //std::cout << rec.normal << std::endl;
                color = Color(rec.normal);
            }
            else {
                color = rayColor(ray);
            }
            outImage.setPixel(x, y, color * 255.0);
        }
    }
    
}

Color MyRT::Camera::rayColor(const Ray& ray) const {
    Vec3 unitDirection = unit_vector(ray.direction());
    double a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * Vec3(1., 1., 1.) + a * Vec3(0.3, 0.5, 1.);
}

void MyRT::Camera::updateCameraGeometry() {
    m_foward = unit_vector(m_lookAt - m_orig);
    m_right = cross(m_up, m_foward);

    double diskRadious = m_focusDistance * tan(radians(m_defocusAngle/2.0));
    m_defocusH = diskRadious * m_up;
    m_defocusW = diskRadious * m_right;

    double height = tan(radians(m_fovAngle)/2.);
    double viewportHeight = 2.0 * height * m_focusDistance;
    double viewportWidth = viewportHeight * m_aspectRatio;
    Vec3 viewportHvec = viewportHeight * m_up;
    Vec3 viewportWvec = viewportWidth * m_right;

    m_pixelDeltaH = viewportHvec / m_imageHeight;
    m_pixelDeltaW = viewportWvec / m_imageWidth;

    Point3 viewportUpLeft = m_orig + (m_focusDistance * m_foward) + (viewportHvec / 2.0) - (viewportWvec /2.0);
    m_pixel00 = viewportUpLeft + (0.5 * (m_pixelDeltaW - m_pixelDeltaH));
    //std::cout << m_foward << std::endl;
}