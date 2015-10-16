#pragma once;
class CSDL_setup
{
public:
	CSDL_setup(bool* quit, int ScreenWidth, int ScreenHeight, bool bordered, bool initialyHidden);
	~CSDL_setup();
	
	SDL_Renderer* GetRenderer();
	SDL_Event* GetMainEvent();

	void begin();
	void end();
	SDL_Event* mainEvent;
	void updateWindow();

	int getScreenWidth();
	int getScreenHeight();
	int getConstantScreenWidth();
	int getConstantScreenHeight();

	void setWindowHidden(bool hidden);

	void setFpsRatio(float ratio);
	double getFpsRatio();

private:

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* windowIcon;

	//screen width and height
	int constantScreenWidth;
	int constantScreenHeight;
	int screenWidth;
	int screenHeight;
	float screenSizeZoom;

	double fpsRatio;
};