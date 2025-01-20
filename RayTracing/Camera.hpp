#ifndef CAMERA_H
#define CAMERA_H

#include "RTutility.hpp"
#include "Image.hpp"
#include "Ray.hpp"
#include "Hittable.hpp"

namespace MyRT
{
	class Camera {
		public:
            Camera();
			Camera(int hScreen, int wScreen);

            void render(Image& outImage, const Hittable& obj) const;
            void updateCameraGeometry();

            void moveLookAt(Vec3 vec) { m_lookAt += unit_vector(vec.x()*m_right + vec.y()*m_up); };
            void moveOrig(Vec3 vec) { m_orig += unit_vector(vec.x() * m_right + vec.y() * m_up); };

            Vec3 getFoward() { return m_foward; }
            Point3 getOrig() { return m_orig; }
            void setOrigin(const Point3& orig) { m_orig = orig; }
            void setLookAt(const Point3& lookAt) { m_lookAt = lookAt; }
            void setImgHeight(const int height) { m_aspectRatio = static_cast<double>(m_imageWidth) / height; m_imageHeight = height; }
            void setImgWidth(const int width) { m_aspectRatio = static_cast<double>(width) / m_imageHeight; m_imageWidth = width; }

        private:

            Color rayColor(const Ray& ray, const Hittable& obj, int depth) const;
            Ray raySample(int i , int j, uint32_t seed) const;

		private:
            int m_imageHeight;
            int m_imageWidth;
            double m_aspectRatio;

            //camera position
            Point3 m_orig;

            //how it is orientated in the scene
            Vec3 m_up;
            Vec3 m_foward;
            Vec3 m_right;

            //where it is looking
            Vec3 m_lookAt;

            //Screen position in the scene
            Point3 m_pixel00;
            Vec3 m_pixelDeltaH;
            Vec3 m_pixelDeltaW;

            //field of view
            double m_fovAngle;

            //Defocus Blur
            double m_defocusAngle;
            double m_focusDistance;
            Vec3 m_defocusH;
            Vec3 m_defocusW;

            //number of rays shoot per pixel
            int m_numberSamples;

            //maximum number of bounces a ray can make 
            int m_limitDepth;
	};
}

#endif
