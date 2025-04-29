#include "Camera.hpp"
#include <iostream>
#include <random>

MyRT::Camera::Camera(int screenWidth, int screenHeight)
    : m_orig(0.0, 0.0, 0.0),
    m_lookAt(0.0, 0.0, 1.0),
    m_up(0.0, 1.0, 0.0),
    m_focusDistance(1.0),
    m_defocusAngle(1.0),
    m_fovAngle(80.0),
    m_numberSamples(10),
    m_limitDepth(100),
    m_imageHeight(screenHeight),
    m_imageWidth(screenWidth),
    m_background(Color()),
    m_aspectRatio(static_cast<double>(screenWidth) / screenHeight) {}

MyRT::Camera::Camera() : Camera(600, 960) {}

inline Color linearToGamma(Color linearColor) {
    double r = linearColor.x();
    double g = linearColor.y();
    double b = linearColor.z();

    r = (r > 0) ? std::sqrt(r) : 0;
    g = (g > 0) ? std::sqrt(g) : 0;
    b = (b > 0) ? std::sqrt(b) : 0;

    return Color(r, g, b);
}

void MyRT::Camera::render(Image &outImage, const Hittable& world) const{
    for (int y = 0; y < m_imageHeight; y++) {
        for (int x = 0; x < m_imageWidth; x++) {
            
            /**/
            Color color = Color();
            for (int sample = 0; sample < m_numberSamples; sample++) {
                //calculates ray vector (not a unit vector)
                Ray ray = raySample( x , y);

                //find the color of the pixel
                HitRecord rec = HitRecord();

                
                color += rayColor(ray, world, 0);
                
            }
            color = color / m_numberSamples;
            //Set the color found on the image
            
            //Normal (normal colors)
            outImage.setPixel(x, y, linearToGamma(color) * 255.0);

            /*
            //Black and White (pretty cool)
            double temp = (color.x() + color.y() + color.z()) / 3.0;
            outImage.setPixel(x, y, Color(temp, temp, temp) * 255.0);
            /**/

            
        }
    }
}

Color MyRT::Camera::rayColor(const Ray& ray, const Hittable& world, int depth) const {
    if (depth > m_limitDepth) {
        return Color(0.0, 0.0, 0.0);
    }

    HitRecord rec = HitRecord();

    if (world.hit(ray, Interval(0.0001, RT_INFINITY), rec)) {
        Ray rOut = Ray();
        Color att = Color();
        Color emittedCol = rec.mat->emitted();
        
        if (rec.mat->scatter(ray, rec, att, rOut)) {

            return ( att * rayColor(rOut, world, depth+1) ) + emittedCol;

        }

        return emittedCol;
    }

    return m_background; //The void
}
 
MyRT::Ray MyRT::Camera::raySample(int i, int j) const {
    Vec3 offset = Vec3::randomUnitVec();
    Vec3 direction = m_pixel00 + ((offset.x() + i) * m_pixelDeltaW) - ((offset.y() + j) * m_pixelDeltaH);

    return Ray(m_orig, direction - m_orig);
}

void MyRT::Camera::updateCameraGeometry() {
    m_foward = unit_vector(m_lookAt - m_orig);
    m_right = unit_vector(cross(m_up, m_foward));
    m_up = unit_vector(cross(m_foward, m_right));

    double diskRadious = m_focusDistance * tan(radians(m_defocusAngle/2.0));
    m_defocusH = diskRadious * m_up;
    m_defocusW = diskRadious * m_right;

    double height = tan(radians(m_fovAngle)/2.);
    double viewportHeight = 2.0 * height * m_focusDistance;
    double viewportWidth = viewportHeight * (static_cast<double>(m_imageWidth) / m_imageHeight);
    Vec3 viewportHvec = viewportHeight * m_up;
    Vec3 viewportWvec = viewportWidth * m_right;

    m_pixelDeltaH = viewportHvec / m_imageHeight;
    m_pixelDeltaW = viewportWvec / m_imageWidth;

    Point3 viewportUpLeft = m_orig + (m_focusDistance * m_foward) + (viewportHvec / 2.0) - (viewportWvec /2.0);
    m_pixel00 = viewportUpLeft + (0.5 * (m_pixelDeltaW - m_pixelDeltaH));
}