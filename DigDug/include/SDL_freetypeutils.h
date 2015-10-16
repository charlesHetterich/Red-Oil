/***************************************************************************
         SDL_freetypeutils.h  -  internal includes for SDL_freetype
                             -------------------
    begin                : Jun 05 2006
    copyright            : (C) 2006 by Ales Teska
    email                : alex (at) cyber (dot) cz
 ***************************************************************************/

#ifndef SDL_FREETYPEUTILS_H_
#define SDL_FREETYPEUTILS_H _

//SDL includes
#include <SDL.h>
#include <SDL_endian.h>

//FreeType2 includes
#include <freetype/internal/ftobjs.h>

#define FT_FLOOR(X)	((X & -64) / 64)
#define FT_CEIL(X)	(((X + 63) & -64) / 64)

//Some macros
#define SDL_FT_FITALIC_ANGLE	0.26f

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
#define UNICODE_SWAP(x)	SDL_Swap16(x)
#else
#define UNICODE_SWAP(x)	(x)
#endif

//Type definition of the load filter function
typedef SDL_RWops * (*SDL_FreeTypeLoad_Filter_t)(const char *Name);

//Actualize Param Font Face pointer - ONLY INTERNAL USE !!!
extern DECLSPEC int SDL_FreeTypeClearFontChangeHistory(SDL_FontParam *Param);
extern DECLSPEC int SDL_FreeTypeGetFontFace(SDL_FontParam *Param);

extern SDL_FontFaceCacheItem	*SDL_FaceCache;
extern FT_Library			SDL_FreeTypeLibrary;
extern SDL_Surface		*SDL_FreeTypeCharSurface;
extern SDL_FreeTypeLoad_Filter_t	SDL_FreeTypeLoad_Filter;

//Loading face into cache
FT_Face SDL_FreeTypeFaceLoad(SDL_RWops *RWops, int Index);

//Predefined file filter
SDL_RWops *SDL_FreeTypeFaceLoad_FileFilter(const char *Name);

//Freetype2 error checking
#define SDL_FreeTypeCheckError(x,y) if (x != 0) {SDL_FreeTypeError(x);y;}
void SDL_FreeTypeError(FT_Error error);

#endif
