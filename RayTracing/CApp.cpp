#include <iostream>
#include <fstream>
#include "CApp.h"
#include "BVHnode.hpp"

uint32_t frame = 0;
uint32_t addingFrames = 1;


void addImage(Image& outImg, Image& adderImg, int numSamples) {
	std::vector<std::vector<Color>> outColors = outImg.m_colorChannel;
	std::vector<std::vector<Color>> adderColors = adderImg.m_colorChannel;

	for (int y = 0; y < outImg.getYSize(); y++) {
		for (int x = 0; x < outImg.getXSize(); x++) {
			Color col = ((outColors.at(x).at(y) * (addingFrames - 1)) + adderColors.at(x).at(y)) / addingFrames;
			outImg.setPixel(x, y, col);
		}
	}

	addingFrames++;
}

void resetImage(Image& outImg) {
	for (int y = 0; y < outImg.getYSize(); y++) {
		for (int x = 0; x < outImg.getXSize(); x++) {
			outImg.setPixel(x, y, Color(0, 0, 0));
		}
	}

	addingFrames = 1;
}

CApp::CApp() {
	m_wWindow = 960; //960 720 480 240
	m_hWindow = 600; //600 450 300 150
	isRunning = true;
	m_pWindow = NULL;
	m_pRenderer = NULL;
}

bool CApp::onInit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	m_pWindow = SDL_CreateWindow("AllanRayTracer", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		m_wWindow, m_hWindow, 
		SDL_WINDOW_SHOWN);

	if (m_pWindow != NULL) {

		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

		m_image.initialize(m_wWindow, m_hWindow, m_pRenderer);

	}
	else {
		return false;
	}
	return true;
}

int CApp::onExecute() {
	SDL_Event event;

	if (onInit() == false) {
		return -1;
	}
	while (isRunning) {
		
		while (SDL_PollEvent(&event) != 0) {
			onEvent(&event);
		}

		onLoop();

		onRender();

		frame++;

		/* For High sample Scenes 
		createFile();
		break;
		/**/
	}
}

int bvhDepth = -1;

void CApp::onEvent(SDL_Event* event) {
	if (event->type == SDL_QUIT) {
		isRunning = false;
	}

	else if(event->type == SDL_KEYDOWN){
		char keyPressed = event->key.keysym.sym;
		MyRT::Camera& cam = m_scene.m_camera;
		switch (keyPressed) {
				// rotate the camera - - - - - - - - - - - - - - - - -
			case 'a':
				cam.moveLookAt(Vec3(-0.1, 0.0, 0.0));
				break;
			case 'd':
				cam.moveLookAt(Vec3(0.1, 0.0, 0.0));
				break;
			case 's':
				cam.moveLookAt(Vec3(0.0, -0.1, 0.0));
				break;
			case 'w':
				cam.moveLookAt(Vec3(0.0, 0.1, 0.0));
				break;
				// rotate towards the center of the world - - - - - -
			case 'e':
				cam.m_lookAt = Vec3(0.0, 0.0, 0.0);
				break;
				// move camera  - - - - - - - - - - - - - - - - - - - 
			case 'j':
				cam.moveOrig(Vec3(-0.1, 0.0, 0.0));
				break;
			case 'l':
				cam.moveOrig(Vec3(0.1, 0.0, 0.0));
				break;
			case 'k':
				cam.moveOrig(Vec3(0.0, -0.1, 0.0));
				break;
			case 'i':
				cam.moveOrig(Vec3(0.0, 0.1, 0.0));
				break;
				// change numSamples
			case 'z':
				cam.m_numberSamples = 1;
				break;
			case 'x':
				cam.m_numberSamples = 15;
				break;
			case 'c':
				cam.m_numberSamples = 100;
				break;
				// make a photo - - - - - - - - - - - - - - - - - - - 
			case 'p':
				createFile();
				std::clog << "photo saved" << std::endl;
				break;
				// change BVH drawing depth
			case 'v':
				
				HittableList world = m_scene.objects;
				bvhDepth = (bvhDepth+1)%5;
				
				BVHnode bvhNode = BVHnode(world, bvhDepth);

				world.add(make_shared<BVHnode>(bvhNode));
				m_scene.m_world = world;
				
				break;
		}
		resetImage(m_image);
	}
	/**/
}

void CApp::onLoop() {
	//m_scene.getCamera().moveOrig(Vec3(0.0, 0.1, 0.0));
}

void CApp::onRender() {
	SDL_SetRenderDrawColor(m_pRenderer, 100, 0, 100, 255);
	SDL_RenderClear(m_pRenderer);

	Image tempImg;
	tempImg.initialize(m_wWindow, m_hWindow, NULL);

	Uint32 start = SDL_GetTicks();
	m_scene.render(tempImg);
	std::clog << "Render time: " << (SDL_GetTicks() - start) << "ms" << ' '  << std::endl;

	addImage(m_image, tempImg, m_scene.m_camera.m_numberSamples);

	start = SDL_GetTicks();
	m_image.display();

	SDL_RenderPresent(m_pRenderer);
}

void CApp::onExit() {
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = NULL;
	SDL_Quit();
}

void CApp::createFile() {
	std::vector<std::vector<Color>> image = m_image.m_colorChannel;
	std::ofstream outFile;
	outFile.open("C:\\Users\\super\\OneDrive\\Desktop\\rayTracingImg.ppm");

	outFile << "P3\n" << m_wWindow << ' ' << m_hWindow << "\n255\n";
	for (int y = 0; y < m_hWindow; y++) {
		for (int x = 0; x < m_wWindow; x++) {
			int r = int(image.at(x).at(y).x());
			int g = int(image.at(x).at(y).y());
			int b = int(image.at(x).at(y).z());

			outFile << r << ' ' << g << ' ' << b << '\n';

		}
	}

	outFile.close();
}
