#ifndef SCENE_HPP
#define SCENE_HPP

#include "Image.hpp"
#include "Camera.hpp"

namespace MyRT
{
	class Scene{
		public:
			Scene();

			bool render(Image& outImage);

			Camera m_camera;

			HittableList world;
	};
}
#endif
