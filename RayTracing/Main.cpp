#include "CApp.h"
#include "RTutility.hpp"
#include <iostream>

int main(int argc, char* args[]) {
	CApp app;
	Vec3 test = Vec3(0.0, -1.0, 5.3);
	std::cout << test << std::endl;
	return app.onExecute();
}