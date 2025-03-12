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

	/*
	if (true) {
		
		int xSize = outImage.getXSize();
		int ySize = outImage.getYSize();
		m_camera.setImgHeight(ySize);
		m_camera.setImgWidth(xSize);

		m_camera.updateCameraGeometry();
		test = true;

	}

	
	//create 3D Scene (for now)
	HittableList world = HittableList();

	/*
	const shared_ptr<Lambertian> LAMB_TEMP1 = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
	const shared_ptr<Lambertian> LAMB_TEMP2 = make_shared<Lambertian>(Color(0.0, 0.9, 0.0));
	const shared_ptr<Diffuse> LIGHT = make_shared<Diffuse>(Color(40.0, 40.0, 40.0));

	/* CUBO di sfere non centrate
		
	world.add(std::make_shared<Sphere>(Point3(3.0, -3.0, 5.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(3.0, -3.0, 10.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(3.0, 3.0, 5.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(3.0, 3.0, 10.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(-3.0, -3.0, 5.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(-3.0, -3.0, 10.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(-3.0, 3.0, 5.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(-3.0, 3.0, 10.0), 0.5, NONE));
	/**/

	/* CUBO di sfere centrate
	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 0.5, LAMB_TEMP1));
	
	world.add(std::make_shared<Sphere>(Point3(5.0, 2.5, 0.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(-5.0, 2.5, 0.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(0.0, 2.5, 5.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(0.0, 2.5, -5.0), 0.5, NONE));

	world.add(std::make_shared<Sphere>(Point3(5.0, -2.5, 0.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(-5.0, -2.5, 0.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(0.0, -2.5, 5.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(0.0, -2.5, -5.0), 0.5, NONE));
	/**/

	/*
	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 1.0, LAMB_TEMP1));

	world.add(std::make_shared<Sphere>(Point3(2.0, 2.0, 2.0), 1.0, LIGHT));
	world.add(std::make_shared<Sphere>(Point3(-2.0, 2.0, -2.0), 1.0, LIGHT));

	world.add(std::make_shared<Sphere>(Point3(1.5, -0.5, 0.0), 0.5, make_shared<Lambertian>(Color(1.0, 0.0, 0.0) )));
	world.add(std::make_shared<Sphere>(Point3(-1.5, -0.5, 0.0), 0.5, make_shared<Lambertian>(Color(0.7, 0.7, 0.0) )));
	world.add(std::make_shared<Sphere>(Point3(0.0, -0.5, 1.5), 0.5, make_shared<Lambertian>(Color(0.0, 0.0, 1.0) )));
	world.add(std::make_shared<Sphere>(Point3(0.0, -0.5, -1.5), 0.5, make_shared<Lambertian>(Color(0.0, 0.7, 0.7))));

	world.add(std::make_shared<Sphere>(Point3(0.0, -1001.0, 0.0), 1000.0, LAMB_TEMP2));
	/**/

	//world.add(std::make_shared<Square>(NONE));

	//render the image