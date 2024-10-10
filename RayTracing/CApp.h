#ifndef CAPP_H
#define CAPP_H

#include <SDL.h>
#include "Image.hpp"
#include "Scene.hpp"

class CApp 
{
	public:
		CApp();

		int onExecute();
		bool onInit();
		void onEvent(SDL_Event* event);
		void onLoop();
		void onRender();
		void onExit();

	private:
		//Beatiful lil goobers
		Image m_image;
		MyRT::Scene m_scene;

		//SDL2
		bool isRunning;
		SDL_Window* m_pWindow;
		SDL_Renderer* m_pRenderer;

		int m_wWindow;
		int m_hWindow;
};

#endif