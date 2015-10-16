#include "SDL.h"
#include <iostream>
#include "SDL_setup.h"

void initializeGamePad(CSDL_setup* csdl_Setup);
void updateButtons();
bool getPressed(int player, int button);
bool getJustPressed(const int button); // use SDLK key code for button