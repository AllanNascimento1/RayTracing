#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>
#include <vector>
#include <string>
#include "Vec3.hpp"

class Image {
	public:
		//Constructors
		Image();

		~Image();

		//Main funcitions
		void initialize(const int xSize, const int ySize, SDL_Renderer* renderer);

		void display();

		//Gets and Sets
		int getXSize() const { return m_xSize; }
		int getYSize() const { return m_ySize; }

		void setPixel(const int x, const int y, const Color color);

	private:
		//utility function
		Uint32 convertColor(const Color color);

		void initTexture();

	private:
		std::vector<std::vector<Color>> m_colorChannel;

		int m_xSize, m_ySize;

		SDL_Renderer* m_pRenderer;
		SDL_Texture* m_pTexture;
};

#endif
