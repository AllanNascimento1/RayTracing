#include <iostream>
#include "CApp.h"

CApp::CApp() {
	m_wWindow = 480; //960 720 480
	m_hWindow = 300; //600 450 300
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

	}
}

void CApp::onEvent(SDL_Event* event) {
	if (event->type == SDL_QUIT) {
		isRunning = false;
	}
	else if(event->type == SDL_KEYDOWN){
		char keyPressed = event->key.keysym.sym;
		switch (keyPressed) {
			case 'a':
				m_scene.getCamera().moveLookAt(Vec3(-0.1, 0.0, 0.0));
				break;
			case 'd':
				m_scene.getCamera().moveLookAt(Vec3(0.1, 0.0, 0.0));
				break;
			case 's':
				m_scene.getCamera().moveLookAt(Vec3(0.0, -0.1, 0.0));
				break;
			case 'w':
				m_scene.getCamera().moveLookAt(Vec3(0.0, 0.1, 0.0));
				break;
		}
	}
}

void CApp::onLoop() {

}

void CApp::onRender() {
	SDL_SetRenderDrawColor(m_pRenderer, 100, 0, 100, 255);
	SDL_RenderClear(m_pRenderer);

	m_scene.render(m_image);

	m_image.display();

	SDL_RenderPresent(m_pRenderer);
}

void CApp::onExit() {
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = NULL;
	SDL_Quit();
}