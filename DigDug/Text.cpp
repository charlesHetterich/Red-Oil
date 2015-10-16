#include "stdafx.h"
#include "Text.h"


CText::CText(CSDL_setup* csdl_Setup)
{
	sdl_Setup = csdl_Setup;
	TTF_Init();

	informalSprite = new Csprites(sdl_Setup, " ", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

	Color3 = { 255, 255, 255 };
	alpha = 255;
}

CText::~CText()
{
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	TTF_Quit();
}

void CText::write(std::string Font, int size, std::string Text, int x, int y, int w, int h, int imageY)
{
	TTF_Init();
	rect.x = x;
	rect.y = y;

	crop.x = 0;
	crop.y = imageY;

	if (fontFile != Font | fontSize != size)
	{
		fontFile = Font;
		fontSize = size;
		font = TTF_OpenFont(fontFile.c_str(), fontSize);
	}

	//render the message to an SDL_Surface, as that's what ttf_renderText_x returns
	if (text != Text)
	{
		if (surf) { SDL_FreeSurface(surf); }
		if (texture) { SDL_DestroyTexture(texture); }
		text = Text;
		if (w != NULL)
			surf = TTF_RenderText_Blended_Wrapped(font, text.c_str(), Color3, w);
		else
			surf = TTF_RenderText_Blended(font, text.c_str(), Color3);



		texture = SDL_CreateTextureFromSurface(sdl_Setup->GetRenderer(), surf);
	}

	if (h != NULL)
	{
		crop.w = surf->w;
		rect.w = surf->w;
		if (crop.h + crop.y < surf->h && crop.y >= 0) { rect.h = h; 	crop.h = h; }
		else if (crop.h + crop.y > surf->h) { rect.h = h - (crop.h + crop.y - surf->h); }
		if (crop.y < 0) { rect.h = h + crop.y; rect.y = y - crop.y; }
	}
	else
	{
		crop.w = surf->w;
		crop.h = surf->h;
		rect.w = surf->w;
		rect.h = surf->h;
	}

	SDL_Rect tempRect;

	tempRect.x = ((rect.x) * informalSprite->getWindowSizeZoom());
	tempRect.y = ((rect.y) * informalSprite->getWindowSizeZoom());
	tempRect.w = rect.w * informalSprite->getWindowSizeZoom();
	tempRect.h = rect.h * informalSprite->getWindowSizeZoom();

	SDL_SetTextureAlphaMod(texture, alpha);
	SDL_SetTextureColorMod(texture, Color3.r, Color3.g, Color3.b);
	SDL_RenderCopy(sdl_Setup->GetRenderer(), texture, &crop, &tempRect);
}

void CText::writeObject(std::string Font, int size, std::string Text, int x, int y, int w, int h, int imageY)
{
	TTF_Init();
	rect.x = x;
	rect.y = y;

	crop.x = 0;
	crop.y = imageY;

	if (fontFile != Font | fontSize != size)
	{
		fontFile = Font;
		fontSize = size;
		font = TTF_OpenFont(fontFile.c_str(), fontSize);
	}

	//render the message to an SDL_Surface, as that's what ttf_renderText_x returns
	if (text != Text)
	{
		if (surf) { SDL_FreeSurface(surf); }
		if (texture) { SDL_DestroyTexture(texture); }
		text = Text;
		if (w != NULL)
			surf = TTF_RenderText_Blended_Wrapped(font, text.c_str(), Color3, w);
		else
			surf = TTF_RenderText_Blended(font, text.c_str(), Color3);

		texture = SDL_CreateTextureFromSurface(sdl_Setup->GetRenderer(), surf);
	}

	if (h != NULL)
	{
		crop.w = surf->w;
		rect.w = surf->w;
		if (crop.h + crop.y < surf->h && crop.y >= 0) { rect.h = h; 	crop.h = h; }
		else if (crop.h + crop.y > surf->h) { rect.h = h - (crop.h + crop.y - surf->h); }
		if (crop.y < 0) { rect.h = h + crop.y; rect.y = y - crop.y; }
	}
	else
	{
		crop.w = surf->w;
		crop.h = surf->h;
		rect.w = surf->w;
		rect.h = surf->h;
	}

	SDL_Rect tempRect;

	tempRect.x = ((rect.x - informalSprite->getFocusX()) * informalSprite->getZoom()) + sdl_Setup->getScreenWidth() / 2;
	tempRect.y = ((rect.y - informalSprite->getFocusY()) * informalSprite->getZoom()) + sdl_Setup->getScreenHeight() / 2;
	tempRect.w = rect.w * informalSprite->getZoom();
	tempRect.h = rect.h * informalSprite->getZoom();

	SDL_SetTextureAlphaMod(texture, alpha);
	SDL_SetTextureColorMod(texture, Color3.r, Color3.g, Color3.b);
	SDL_RenderCopy(sdl_Setup->GetRenderer(), texture, &crop, &tempRect);
}

void CText::writeCentered(std::string Font, int size, std::string Text, int x, int y, int w, int h, int imageY)
{
	TTF_Init();
	rect.x = x;
	rect.y = y;

	crop.x = 0;
	crop.y = imageY;

	if (fontFile != Font | fontSize != size)
	{
		fontFile = Font;
		fontSize = size;
		font = TTF_OpenFont(fontFile.c_str(), fontSize);
	}

	//render the message to an SDL_Surface, as that's what ttf_renderText_x returns
	if (text != Text)
	{
		if (surf) { SDL_FreeSurface(surf); }
		if (texture) { SDL_DestroyTexture(texture); }
		text = Text;
		if (w != NULL)
			surf = TTF_RenderText_Blended_Wrapped(font, text.c_str(), Color3, w);
		else
			surf = TTF_RenderText_Blended(font, text.c_str(), Color3);

		texture = SDL_CreateTextureFromSurface(sdl_Setup->GetRenderer(), surf);
	}

	if (h != NULL)
	{
		crop.w = surf->w;
		rect.w = surf->w;
		if (crop.h + crop.y < surf->h && crop.y >= 0) { rect.h = h; 	crop.h = h; }
		else if (crop.h + crop.y > surf->h) { rect.h = h - (crop.h + crop.y - surf->h); }
		if (crop.y < 0) { rect.h = h + crop.y; rect.y = y - crop.y; }
	}
	else
	{
		crop.w = surf->w;
		crop.h = surf->h;
		rect.w = surf->w;
		rect.h = surf->h;
	}

	rect.x = x - rect.w / 2;

	SDL_Rect tempRect;

	tempRect.x = ((rect.x) * informalSprite->getWindowSizeZoom());
	tempRect.y = ((rect.y) * informalSprite->getWindowSizeZoom());
	tempRect.w = rect.w * informalSprite->getWindowSizeZoom();
	tempRect.h = rect.h * informalSprite->getWindowSizeZoom();

	SDL_SetTextureAlphaMod(texture, alpha);
	SDL_SetTextureColorMod(texture, Color3.r, Color3.g, Color3.b);
	SDL_RenderCopy(sdl_Setup->GetRenderer(), texture, &crop, &tempRect);
}

void CText::writeObjectCentered(std::string Font, int size, std::string Text, int x, int y, int w, int h, int imageY)
{

	TTF_Init();
	rect.x = x;
	rect.y = y;

	crop.x = 0;
	crop.y = imageY;

	if (fontFile != Font | fontSize != size)
	{
		fontFile = Font;
		fontSize = size;
		font = TTF_OpenFont(fontFile.c_str(), fontSize);
	}

	//render the message to an SDL_Surface, as that's what ttf_renderText_x returns
	if (text != Text)
	{
		if (surf) { SDL_FreeSurface(surf); }
		if (texture) { SDL_DestroyTexture(texture); }
		text = Text;
		if (w != NULL)
			surf = TTF_RenderText_Blended_Wrapped(font, text.c_str(), Color3, w);
		else
			surf = TTF_RenderText_Blended(font, text.c_str(), Color3);

		texture = SDL_CreateTextureFromSurface(sdl_Setup->GetRenderer(), surf);
	}

	if (h != NULL)
	{
		crop.w = surf->w;
		rect.w = surf->w;
		if (crop.h + crop.y < surf->h && crop.y >= 0) { rect.h = h; 	crop.h = h; }
		else if (crop.h + crop.y > surf->h) { rect.h = h - (crop.h + crop.y - surf->h); }
		if (crop.y < 0) { rect.h = h + crop.y; rect.y = y - crop.y; }
	}
	else
	{
		crop.w = surf->w;
		crop.h = surf->h;
		rect.w = surf->w;
		rect.h = surf->h;
	}
	
	rect.x = x - rect.w / 2;

	SDL_Rect tempRect;

	tempRect.x = ((rect.x - informalSprite->getFocusX()) * informalSprite->getZoom()) + sdl_Setup->getScreenWidth() / 2;
	tempRect.y = ((rect.y - informalSprite->getFocusY()) * informalSprite->getZoom()) + sdl_Setup->getScreenHeight() / 2;
	tempRect.w = rect.w * informalSprite->getZoom();
	tempRect.h = rect.h * informalSprite->getZoom();

	

	SDL_SetTextureAlphaMod(texture, alpha);
	SDL_SetTextureColorMod(texture, Color3.r, Color3.g, Color3.b);
	SDL_RenderCopy(sdl_Setup->GetRenderer(), texture, &crop, &tempRect);
}

void CText::setColor(int r, int g, int b)
{
	Color3 = { r, g, b };
}

void CText::setAlpha(int newAlpha)
{
	alpha = newAlpha;
}

int CText::getAlpha()
{
	return alpha;
}