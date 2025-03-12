#include "CApp.h"
#include <iostream>

int main(int argc, char* args[]) {
	CApp app;

	switch (1) {
		default:
		case 1:
			//app.m_scene = lightTest(app);
			break;
		case 2:
			break;
	}

	return app.onExecute();

}

MyRT::Scene lightTest(const CApp& app) {
	MyRT::Scene outScene = MyRT::Scene();
	MyRT::Camera cam = MyRT::Camera(app.m_hWindow, app.m_wWindow);
}