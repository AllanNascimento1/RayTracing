#include "Scene.hpp"

#include "RTutility.hpp"
#include "Hittable.hpp"
#include "Material.hpp"

#include "Sphere.hpp"
#include "Square.hpp"

MyRT::Scene::Scene() {
	m_camera = Camera();
}

bool MyRT::Scene::render(Image& outImage) {
	m_camera.updateCameraGeometry();

	m_camera.render(outImage, m_world);
	
	return true;
}