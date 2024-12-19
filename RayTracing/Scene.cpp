#include "Scene.hpp"

#include "RTutility.hpp"
#include "Hittable.hpp"
#include "HittableList.hpp"
#include "Material.hpp"

#include "Sphere.hpp"
#include "Square.hpp"

MyRT::Scene::Scene() {
	m_camera = Camera();

	//initialize camera
	m_camera.setLookAt(Point3(0.0, 0.0, 0.0));
	m_camera.setOrigin(Point3(0.0, 0.0, -2.0));
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

	const shared_ptr<Material> NONE = make_shared<Material>(Material());
	const shared_ptr<Lambertian> LAMB_TEMP1 = make_shared<Lambertian>(Color(1.0, 0.0, 1.0));

	/*
	world.add(std::make_shared<Sphere>(Point3(3.0, -3.0, 5.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(3.0, -3.0, 10.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(3.0, 3.0, 5.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(3.0, 3.0, 10.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(-3.0, -3.0, 5.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(-3.0, -3.0, 10.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(-3.0, 3.0, 5.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(-3.0, 3.0, 10.0), 0.5));
	/**/

	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(0.0, 1.0, 0.0), 0.1, NONE));
	world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, 0.0), 0.1, NONE));
	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.1, NONE));

	//world.add(std::make_shared<Square>());

	//render the image
	m_camera.render(outImage, world);

	return true;
}