#include "CApp.h"
#include "Sphere.hpp"
#include "AaBoundingBox.hpp"
#include <iostream>

using namespace MyRT;

static Scene dayLightTest(const CApp& app) {
	Scene outScene = Scene();
	Camera cam = Camera(app.m_wWindow, app.m_hWindow);
	HittableList world = HittableList();

	cam.m_lookAt = Point3(0.0, 0.0, 0.0);
	cam.m_orig = Point3(3.8, 6.4, -4.5);
	cam.m_up = Vec3(0.0, 1.0, 0.0);

	cam.m_focusDistance = 1.0;
	cam.m_defocusAngle = 1.0;
	cam.m_fovAngle = 80.0;

	cam.m_numberSamples = 2;
	cam.m_limitDepth = 100;

	cam.m_background = Color(0.3, 0.5, 1.);


	const shared_ptr<Lambertian> LAMB_TEMP1 = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
	const shared_ptr<Lambertian> LAMB_TEMP2 = make_shared<Lambertian>(Color(0.0, 0.9, 0.0));
	const shared_ptr<Diffuse> LIGHT = make_shared<Diffuse>(Color(40.0, 40.0, 40.0));
	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 1.0, LAMB_TEMP1));

	world.add(std::make_shared<Sphere>(Point3(2.0, 2.0, 2.0), 1.0, LIGHT));
	
	world.add(std::make_shared<Sphere>(Point3(-2.0, 2.0, -2.0), 1.0, LIGHT));

	world.add(std::make_shared<Sphere>(Point3(1.5, -0.5, 0.0), 0.5, make_shared<Lambertian>(Color(1.0, 0.01, 0.01))));
	world.add(std::make_shared<Sphere>(Point3(-1.5, -0.5, 0.0), 0.5, make_shared<Lambertian>(Color(0.7, 0.7, 0.01))));
	world.add(std::make_shared<Sphere>(Point3(0.0, -0.5, 1.5), 0.5, make_shared<Lambertian>(Color(0.01, 0.01, 1.0))));
	world.add(std::make_shared<Sphere>(Point3(0.0, -0.5, -1.5), 0.5, make_shared<Lambertian>(Color(0.01, 0.7, 0.7))));

	world.add(std::make_shared<Sphere>(Point3(0.0, -1001.0, 0.0), 1000.0, LAMB_TEMP2));
	

	outScene.m_camera = cam;
	outScene.m_world = world;

	return outScene;
}

static Scene abbTest(const CApp& app) {
	Scene outScene = Scene();
	Camera cam = Camera(app.m_wWindow, app.m_hWindow);
	HittableList world = HittableList();

	cam.m_lookAt = Point3(0.0, 0.0, 0.0);
	cam.m_orig = Point3(0.0, 0.0, -2.0);
	cam.m_up = Vec3(0.0, 1.0, 0.0);

	cam.m_focusDistance = 1.0;
	cam.m_defocusAngle = 1.0;
	cam.m_fovAngle = 80.0;

	cam.m_numberSamples = 2;
	cam.m_limitDepth = 100;

	cam.m_background = Color(0.3, 0.5, 1.0);

	const shared_ptr<Diffuse> LIGHT = make_shared<Diffuse>(Color(1.0, 1.0, 1.0));
	const shared_ptr<Lambertian> LAMB_TEMP2 = make_shared<Lambertian>(Color(0.0, 0.9, 0.0));

	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 0.5, LAMB_TEMP2));
	world.add(std::make_shared<Sphere>(Point3(0.0, 100.5, 0.0), 100.0, LAMB_TEMP2));

	/*
	world.add(std::make_shared<Sphere>(Point3(1.5, 0.0, 0.0), 0.5, LIGHT));
	world.add(std::make_shared<Sphere>(Point3(-1.5, 0.0, 0.0), 0.5, LIGHT));
	world.add(std::make_shared<Sphere>(Point3(0.0, 1.5, 0.0), 0.5, LIGHT));
	world.add(std::make_shared<Sphere>(Point3(0.0, -1.5, 0.0), 0.5, LIGHT));
	/**/

	outScene.m_camera = cam;
	outScene.m_world = world;

	return outScene;
}

int main(int argc, char* args[]) {
	CApp app;

	switch (2) {
		default:
		case 1:
			app.m_scene = dayLightTest(app);
			break;
		case 2:
			app.m_scene = abbTest(app);
			break;
	}

	return app.onExecute();

}