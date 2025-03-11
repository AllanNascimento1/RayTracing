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
	m_camera.m_lookAt = Point3(0.0, 0.0, 0.0);
	m_camera.m_orig = Point3(2.0, 1.0, -3.0);
}

bool test = false;

bool MyRT::Scene::render(Image& outImage) {

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

	/**/
	const shared_ptr<Material> NONE = make_shared<Material>(Material());
	const shared_ptr<Lambertian> LAMB_TEMP1 = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
	const shared_ptr<Lambertian> LAMB_TEMP2 = make_shared<Lambertian>(Color(0.0, 0.9, 0.0));

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

	/**/
	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 1.0, LAMB_TEMP1));

	world.add(std::make_shared<Sphere>(Point3(1.5, -0.5, 0.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(-1.5, -0.5, 0.0), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(0.0, -0.5, 1.5), 0.5, NONE));
	world.add(std::make_shared<Sphere>(Point3(0.0, -0.5, -1.5), 0.5, NONE));

	world.add(std::make_shared<Sphere>(Point3(0.0, -51.0, 0.0), 50.0, LAMB_TEMP2));
	/**/

	//world.add(std::make_shared<Square>(NONE));

	//render the image
	m_camera.render(outImage, world);
	
	return true;
}