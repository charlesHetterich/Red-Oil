#include "Input.h"

SDL_Joystick* gamePad;
int deadZone;
CSDL_setup* sdl_Setup;
bool buttonPressed[2][9];
const Uint8 *state;

void initializeGamePad(CSDL_setup* csdl_Setup)
{
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
	{
		std::cout << "no controller connected!";
	}
	gamePad = SDL_JoystickOpen(0);
	if (gamePad == NULL)
	{
		std::cout << "no controller connected";
	}

	deadZone = 8000;
	sdl_Setup = csdl_Setup;
}

bool getPressed(int player, int button)
{
	return buttonPressed[player][button];
}

bool getJustPressed(const int button)
{

	enum
	{
	//	x = SDL_SCANCODE_TO_KEYCODE((const int)button)
	};
	const int x = (const int)button;
	switch (sdl_Setup->GetMainEvent()->type)
	{
	case SDL_KEYDOWN:

		switch (sdl_Setup->GetMainEvent()->key.keysym.sym)
		{
		case SDLK_0:
			return true;
			break;
		}
		break;

	default:
		break;
	}

	return false;
}

void updateButtons()
{
	state = SDL_GetKeyboardState(NULL);
	SDL_JoystickUpdate();

	//player 1
	if (state[SDL_SCANCODE_A] | (SDL_JoystickGetAxis(gamePad, 0) < 0 && abs(SDL_JoystickGetAxis(gamePad, 0)) > deadZone))
		buttonPressed[0][0] = true;
	else
		buttonPressed[0][0] = false;
	if (state[SDL_SCANCODE_D] | (SDL_JoystickGetAxis(gamePad, 0) > 0 && abs(SDL_JoystickGetAxis(gamePad, 0)) > deadZone))
		buttonPressed[0][1] = true;
	else
		buttonPressed[0][1] = false;
	if (state[SDL_SCANCODE_W] | (SDL_JoystickGetAxis(gamePad, 1) < 0 && abs(SDL_JoystickGetAxis(gamePad, 1)) > deadZone))
		buttonPressed[0][2] = true;
	else
		buttonPressed[0][2] = false;
	if (state[SDL_SCANCODE_S] | (SDL_JoystickGetAxis(gamePad, 1) > 0 && abs(SDL_JoystickGetAxis(gamePad, 1)) > deadZone))
		buttonPressed[0][3] = true;
	else
		buttonPressed[0][3] = false;
	if (state[SDL_SCANCODE_RETURN] | SDL_JoystickGetButton(gamePad, 10))
		buttonPressed[0][4] = true;
	else
		buttonPressed[0][4] = false;
	if (state[SDL_SCANCODE_ESCAPE])
		buttonPressed[0][5] = true;
	else
		buttonPressed[0][5] = false;
	if (state[SDL_SCANCODE_I])
		buttonPressed[0][6] = true;
	else
		buttonPressed[0][6] = false;
	if (state[SDL_SCANCODE_RSHIFT])
		buttonPressed[0][7] = true;
	else
		buttonPressed[0][7] = false;
	if (state[SDL_SCANCODE_F1])
		buttonPressed[0][8] = true;
	else
		buttonPressed[0][8] = false;

	//player 2
	if (state[SDL_SCANCODE_LEFT])
		buttonPressed[1][0] = true;
	else
		buttonPressed[1][0] = false;
	if (state[SDL_SCANCODE_RIGHT])
		buttonPressed[1][1] = true;
	else
		buttonPressed[1][1] = false;
	if (state[SDL_SCANCODE_UP])
		buttonPressed[1][2] = true;
	else
		buttonPressed[1][2] = false;
	if (state[SDL_SCANCODE_DOWN])
		buttonPressed[1][3] = true;
	else
		buttonPressed[1][3] = false;
	if (state[SDL_SCANCODE_RSHIFT])
		buttonPressed[1][4] = true;
	else
		buttonPressed[1][4] = false;
	if (state[SDL_SCANCODE_ESCAPE])
		buttonPressed[1][5] = true;
	else
		buttonPressed[1][5] = false;
	if (state[SDL_SCANCODE_I])
		buttonPressed[1][6] = true;
	else
		buttonPressed[1][6] = false;
}