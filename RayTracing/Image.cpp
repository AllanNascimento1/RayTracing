#include "Image.hpp"
#include "Interval.hpp"

Image::Image() {
	m_xSize = 0;
	m_ySize = 0;
	m_pTexture = NULL;
}

Image::~Image() {
	if(m_pTexture != NULL){
		SDL_DestroyTexture(m_pTexture);
	}
}

void Image::initialize(const int xSize, const int ySize, SDL_Renderer* renderer) {
	m_colorChannel.resize(xSize, std::vector<Color>(ySize, Color()));

	m_xSize = xSize;
	m_ySize = ySize;

	m_pRenderer = renderer;
	
	initTexture();
}

void Image::display() {
	Uint32* tempPixels = new Uint32[m_xSize * m_ySize];

	//memset(array, value, size) - sets array elements to the value
	memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));

	for (int x = 0; x < m_xSize; x++) {
		for (int y = 0; y < m_ySize; y++) {
			tempPixels[(y * m_xSize) + x] = convertColor(m_colorChannel.at(x).at(y));
		}
	}

	SDL_UpdateTexture(m_pTexture, NULL, tempPixels, m_xSize * sizeof(Uint32));

	//when using new u need to delete after
	delete[] tempPixels;

	SDL_Rect srcRect, bounds;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = m_xSize;
	srcRect.h = m_ySize;
	bounds = srcRect;
	SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
}

void Image::setPixel(const int x, const int y, Color color) {
	Interval control = Interval(0.0, 255.0);
	color.e[0] = control.floor(color.x());
	color.e[1] = control.floor(color.y());
	color.e[2] = control.floor(color.z());

	m_colorChannel.at(x).at(y) = color;
}

Uint32 Image::convertColor(const Color color) {
	unsigned char r = static_cast<unsigned char>(color.x());
	unsigned char g = static_cast<unsigned char>(color.y());
	unsigned char b = static_cast<unsigned char>(color.z());
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
#else
	Uint32 pixelColor = (255 << 24) + (r << 16) + (g << 8) + b;
#endif

	return pixelColor;
}

void Image::initTexture() {
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	amask = 0xff000000;
	bmask = 0x00ff0000;
	gmask = 0x0000ff00;
	rmask = 0x000000ff;
#endif
	if (m_pTexture != NULL) {
		SDL_DestroyTexture(m_pTexture);
	}

	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}