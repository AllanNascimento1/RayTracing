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

			Camera& getCamera() { return m_camera; }

		private:


		private:
			Camera m_camera;

	};
}
#endif
