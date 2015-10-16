#include "stdafx.h"
#include "sprites.h"

int focusX = 0;
int focusY = 0;
float zoom = 1;
float windowSizeZoom = 1;
float zoomNumber;

Csprites::Csprites(CSDL_setup* csdl_Setup, std::string FilePath, int x, int y, int w, int h, int imageX, int imageY, int imageW, int imageH)
{
		sdl_Setup = csdl_Setup;

		image = IMG_LoadTexture(sdl_Setup->GetRenderer(), FilePath.c_str());
		if (image == NULL && FilePath != " ")
		{
			std::cout << "could not load: " << FilePath << "\n";
		}

		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;

		crop.x = imageX;
		crop.y = imageY;
		crop.w = imageW;
		crop.h = imageH;

		red = 255;
		green = 255;
		blue = 255;

		alpha = 255;
}

Csprites::~Csprites()
{
}

void Csprites::drawStatic(SDL_Texture* texture)
{
	SDL_Rect tempRect;

	tempRect.x = ((rect.x) * windowSizeZoom);
	tempRect.y = ((rect.y) * windowSizeZoom);
	tempRect.w = rect.w * windowSizeZoom;
	tempRect.h = rect.h * windowSizeZoom;

	if (texture)
	{
		SDL_SetTextureColorMod(texture, red, green, blue);
		SDL_SetTextureAlphaMod(texture, alpha);
		SDL_RenderCopyEx(sdl_Setup->GetRenderer(), texture, &crop, &tempRect, angle, NULL, flip);
	}
	else
		SDL_RenderCopyEx(sdl_Setup->GetRenderer(), image, &crop, &tempRect, angle, NULL, flip);
}

void Csprites::drawObject(SDL_Texture* texture)
{
	SDL_Rect tempRect;

	tempRect.w = roundf((float)rect.w * (zoom * windowSizeZoom));
	tempRect.h = roundf((float)rect.h *  (zoom * windowSizeZoom));
	tempRect.x = roundf(((float)rect.x - focusX) * (zoom * windowSizeZoom)) + sdl_Setup->getScreenWidth() / 2;
	tempRect.y = roundf(((float)rect.y - focusY) * (zoom * windowSizeZoom)) + sdl_Setup->getScreenHeight() / 2;
	if (texture)
	{
		SDL_SetTextureColorMod(texture, red, green, blue);
		SDL_SetTextureAlphaMod(texture, alpha);
		SDL_RenderCopyEx(sdl_Setup->GetRenderer(), texture, &crop, &tempRect, angle, NULL, flip);
	}
	else
		SDL_RenderCopyEx(sdl_Setup->GetRenderer(), image, &crop, &tempRect, angle, NULL, flip);
}

void Csprites::setWindowSizeZoom()
{
	windowSizeZoom = (float)sdl_Setup->getScreenHeight() / (float)sdl_Setup->getConstantScreenHeight();
	std::cout << windowSizeZoom << "\n";
}

float Csprites::getWindowSizeZoom()
{
	return windowSizeZoom;
}

void Csprites::takeScreenShot()
{
	SDL_Surface *sshot = SDL_CreateRGBSurface(0, sdl_Setup->getScreenWidth(), sdl_Setup->getScreenHeight(), 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(sdl_Setup->GetRenderer(), NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);

	//time_t t = time(0);
	//struct tm * now = NULL;
	//localtime_s(now, &t);

	//std::string timeString = "screenshots/" + std::to_string(now->tm_year + 1900) + "_" + std::to_string(now->tm_mon + 1) + "_" + std::to_string(now->tm_mday) + "_" + std::to_string(now->tm_hour) + "_" + std::to_string(now->tm_min) + "_" + std::to_string(now->tm_sec) + ".bmp";


	SDL_SaveBMP(sshot, "screenshots/screenshot.bmp");
	SDL_FreeSurface(sshot);
	std::cout << "hi";
}

void Csprites::setZoom(float newZoom)
{
	zoom = newZoom;
	zoomNumber = log(zoom) / log(1.01);
}

float Csprites::getZoom()
{
	return zoom*windowSizeZoom;
}

void Csprites::setZoomNumber(float newZoomNumber)
{
	zoomNumber = newZoomNumber;
	zoom = pow(1.01, zoomNumber);
}

float Csprites::getZoomNumber()
{
	return zoomNumber;
}

void Csprites::setFocusX(int focus)
{
	focusX = focus;
}

int Csprites::getFocusX()
{
	return focusX;
}

void Csprites::setFocusY(int focus)
{
	focusY = focus;
}

int Csprites::getFocusY()
{
	return focusY;
}

void Csprites::setAlpha(int newAlpha)
{

	alpha = newAlpha;
	SDL_SetTextureAlphaMod(image, alpha);
	
}

int Csprites::getAlpha()
{
	return alpha;
}

void Csprites::setAngle(double newAngle)
{
	angle = newAngle;
}

double Csprites::getAngle()
{
	return angle;
}

void Csprites::setCrop(int x, int y, int w, int h)
{
	crop = { x, y, w, h };
}

int Csprites::getX()
{
	return rect.x;
}

void Csprites::setX(int x)
{
  	rect.x = x;
}

int Csprites::getY()
{
	return rect.y;
}

void Csprites::setY(int y)
{
	rect.y = y;
}

int Csprites::getW()
{
	return rect.w;
}

void Csprites::setW(int w)
{
	rect.w = w;
}

int Csprites::getH()
{
	return rect.h;
}

void Csprites::setH(int h)
{
	rect.h = h;
}

SDL_Rect Csprites::getRect()
{
	return rect;
}

void Csprites::setFlip(SDL_RendererFlip newFlip)
{
	flip = newFlip;
}

void Csprites::setColorMod(int r, int g, int b)
{
	if (image)
		SDL_SetTextureColorMod(image, r, g, b);
	red = r;
	green = g;
	blue = b;
}

int Csprites::getFrame()
{
	return frame;
}

void Csprites::setFrame(int newFrame)
{
	frame = newFrame;
	crop.x = crop.w * frame;
}

int Csprites::getFrameRow()
{
	return frameRow;
}

void Csprites::setFrameRow(int newFrameRow)
{
	frameRow = newFrameRow;
	crop.y = crop.h * frameRow;
}

SDL_Texture* Csprites::getTexture()
{
	return image;
}