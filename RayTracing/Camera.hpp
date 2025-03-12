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

            void render(Image& outImage, const Hittable& world) const;
            void updateCameraGeometry();

            void moveLookAt(Vec3 vec) { m_lookAt += unit_vector(vec.x()*m_right + vec.y()*m_up); };
            void moveOrig(Vec3 vec) { m_orig += unit_vector(vec.x() * m_right + vec.y() * m_up); };

            Vec3 getFoward() { return m_foward; }
            void setImgHeight(const int height) { m_aspectRatio = static_cast<double>(m_imageWidth) / height; m_imageHeight = height; }
            void setImgWidth(const int width) { m_aspectRatio = static_cast<double>(width) / m_imageHeight; m_imageWidth = width; }

            //image
            int m_imageHeight;
            int m_imageWidth;

            //camera position
            Point3 m_orig;

            //where it is looking
            Vec3 m_lookAt;

            //field of view
            double m_fovAngle;

            //number of rays shoot per pixel
            int m_numberSamples;

            //maximum number of bounces a ray can make 
            int m_limitDepth;

            //Defocus Blur
            double m_defocusAngle;
            double m_focusDistance;

        private:

            Color rayColor(const Ray& ray, const Hittable& world, int depth) const;
            Ray raySample(int i , int j) const;

		private:
            double m_aspectRatio;

            //how it is orientated in the scene
            Vec3 m_up;
            Vec3 m_foward;
            Vec3 m_right;

            //Screen position in the scene
            Point3 m_pixel00;
            Vec3 m_pixelDeltaH;
            Vec3 m_pixelDeltaW;

            //Defocus
            Vec3 m_defocusH;
            Vec3 m_defocusW;
	};
}

#endif
