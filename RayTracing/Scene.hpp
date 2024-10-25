#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <SDL.h>
#include "Image.hpp"
#include "Camera.hpp"
#include "RTutility.hpp"

#include "Hittable.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"

namespace MyRT
{
	class Scene{
		public:
			Scene();

			bool render(Image& outImage);

			Camera& getCamera() { return m_camera; }

		private:


		private:
			Camera m_camera;

	};
}
#endif
