/***************************************************************************
                SDL_freetypecoding.c  -  Unicode/ascii functions
                             -------------------
    begin                : Wed Sep 5 2001
    copyright            : (C) 2001 by Ales Teska
    email                : alex (at) cyber (dot) cz
 ***************************************************************************/

#include "SDL_freetype.h"
#include "SDL_freetypeutils.h"

int SDL_RenderTextASCII(SDL_Surface *Surface, int BaseLineX, int BaseLineY, const char *Text, SDL_FontParam *ParamIn, SDL_FontParam *ParamOut)
 {
	int	size,i;
	Uint16	*UnicodeText;

	if ((Text == NULL) || (*Text == 0)) return(0);

	size = (strlen(Text)+1);
	UnicodeText = malloc(size * sizeof(Uint16));	
	for ( i=0; i < size; i++) UnicodeText[i] = UNICODE_SWAP(((const unsigned char *)Text)[i]);

	i = SDL_RenderTextUNICODE(Surface, BaseLineX, BaseLineY, UnicodeText, ParamIn, ParamOut);
	free(UnicodeText);
	return(i);

 }

int SDL_RenderTextWIDE(SDL_Surface *Surface, int BaseLineX, int BaseLineY, const wchar_t *Text, SDL_FontParam *ParamIn, SDL_FontParam *ParamOut)
 {
	int	size,i;
	Uint16	*UnicodeText;

	if ((Text == NULL) || (*Text == 0)) return(0);

	for (size=0; Text[size] != 0; size ++);

	UnicodeText = malloc(size * sizeof(Uint16));	
	for ( i=0; i < size; i++) UnicodeText[i] = UNICODE_SWAP(Text[i]);

	i = SDL_RenderTextUNICODE(Surface, BaseLineX, BaseLineY, UnicodeText, ParamIn, ParamOut);
	free(UnicodeText);
	return(i);

 }

int SDL_GetTextSizeASCII(const char *Text, SDL_FontParam *ParamIn, SDL_FontParam *ParamOut, int *Width, int *Height, int *BaselineY, int *FontLineSkip, int *FontHeight, int *Ascent, int *Descent)
 {
	int	size,i;
	Uint16	*UnicodeText;

	if ((Text == NULL) || (*Text == 0)) return(0);

	size = (strlen(Text)+1);
	UnicodeText = malloc(size * sizeof(Uint16));	
	for ( i=0; i < size; i++) UnicodeText[i] = UNICODE_SWAP(((const unsigned char *)Text)[i]);

	i = SDL_GetTextSizeUNICODE(UnicodeText, ParamIn, ParamOut, Width, Height, BaselineY, FontLineSkip, FontHeight, Ascent, Descent);
	free(UnicodeText);
	return(i);

 }

int SDL_GetTextSizeWIDE(const wchar_t *Text, SDL_FontParam *ParamIn, SDL_FontParam *ParamOut, int *Width, int *Height, int *BaselineY, int *FontLineSkip, int *FontHeight, int *Ascent, int *Descent)
 {
	int	size,i;
	Uint16	*UnicodeText;

	if ((Text == NULL) || (*Text == 0)) return(0);

	for (size=0; Text[size] != 0; size ++);

	UnicodeText = malloc(size * sizeof(Uint16));	
	for ( i=0; i < size; i++) UnicodeText[i] = UNICODE_SWAP(Text[i]);

	i = SDL_GetTextSizeUNICODE(UnicodeText, ParamIn, ParamOut, Width, Height, BaselineY, FontLineSkip, FontHeight, Ascent, Descent);
	free(UnicodeText);
	return(i);

 }
