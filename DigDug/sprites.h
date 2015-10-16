#pragma once;
#include "SDL_setup.h"
class Csprites
{
public:
	Csprites(CSDL_setup* csdl_Setup, std::string FilePath, int x, int y, int w, int h, int imageX, int imageY, int imageW, int imageH);
	~Csprites();

	//drawing
	void drawObject(SDL_Texture* texture);
	void drawStatic(SDL_Texture* texture);

	//image variables
	SDL_Texture* getTexture();
	int getFrame();
	void setFrame(int newFrame);
	int getFrameRow();
	void setFrameRow(int newFrameRow);
	void setAlpha(int newAlpha);
	int getAlpha();
	void setCrop(int x, int y, int w, int h);
	void setFlip(SDL_RendererFlip newFlip);
	void setColorMod(int r, int g, int b);

	//rectangle variables
	SDL_Rect getRect();
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	int getW();
	void setW(int w);
	int getH();
	void setH(int h);
	void setAngle(double newAngle);
	double getAngle();

	//global variables
	void takeScreenShot();
	void setWindowSizeZoom();
	float getWindowSizeZoom();
	void setZoom(float newZoom);
	float getZoom();
	void setZoomNumber(float newZoomNumber);
	float getZoomNumber();
	void setFocusX(int focus);
	int getFocusX();
	void setFocusY(int focus);
	int getFocusY();
	
private:


	
	//rectangle variables
	SDL_Rect rect;//the actual objects dimentions
	double angle;

	//image variables
	SDL_Texture* image;
	SDL_Rect crop;//dimentions of the image on sprite map
	int alpha;
	int frame;
	int frameRow;
	int red, green, blue;

	SDL_RendererFlip flip;

	CSDL_setup* sdl_Setup;
};