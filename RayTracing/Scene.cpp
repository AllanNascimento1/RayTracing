#include "Scene.hpp"

MyRT::Scene::Scene() {
	m_camera = Camera();

	//initialize camera
	m_camera.setLookAt(Point3(0.0, 0.0, 2.0));
	m_camera.setOrigin(Point3(0.0, 0.0, 0.0));
}

double test = 0;

bool MyRT::Scene::render(Image& outImage) {
	
	int xSize = outImage.getXSize();
	int ySize = outImage.getYSize();
	m_camera.setImgHeight(ySize);
	m_camera.setImgWidth(xSize);

	m_camera.updateCameraGeometry();

	//create 3D Scene (for now)
	HittableList world = HittableList();

	world.add(std::make_shared<Sphere>(Point3(1.0, -1.0, 2.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(1.0, -1.0, 3.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(1.0, 1.0, 2.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(1.0, 1.0, 3.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(-1.0, -1.0, 2.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(-1.0, -1.0, 3.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(-1.0, 1.0, 2.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(-1.0, 1.0, 3.0), 0.5));

	//render the image
	m_camera.render(outImage, world);

	//test++;
	//double test2 = 0.9 * sin(test / 3.0);
	//m_camera.setOrigin(Point3(0.0+2.0*cos(test/6.0), 0.0, 2.0 + 2.0*sin(test / 6.0)));

	return true;
}