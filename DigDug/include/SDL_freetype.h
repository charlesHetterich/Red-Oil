/***************************************************************************
        SDL_freetype.h  -  main and only include file for SDL_freetype
                             -------------------
    begin                : Thu Aug 30 2001
    copyright            : (C) 2001 by Ales Teska
    email                : alex (at) cyber (dot) cz
 ***************************************************************************/

#ifndef SDL_FREETYPE_H_
#define SDL_FREETYPE_H_

#include <SDL.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_ERRORS_H
#include FT_CACHE_H
#include FT_CACHE_IMAGE_H
#include FT_CACHE_SMALL_BITMAPS_H
#include FT_SYSTEM_H

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* Printable format: "%d.%d.%d", MAJOR, MINOR, PATCHLEVEL
*/
#define SDL_FREETYPE_MAJOR_VERSION   1
#define SDL_FREETYPE_MINOR_VERSION   0
#define SDL_FREETYPE_PATCHLEVEL      0

/* This macro can be used to fill a version structure with the compile-time
 * version of the SDL_ttf library.
 */
#define SDL_FREETYPE_VERSION(X)                                         \
{                                                                       \
    (X)->major = SDL_FREETYPE_MAJOR_VERSION;                            \
    (X)->minor = SDL_FREETYPE_MINOR_VERSION;                            \
    (X)->patch = SDL_FREETYPE_PATCHLEVEL;                               \
}

const SDL_version *FreeType_Linked_Version();

//Format character definitions
#define SDL_FTFORMAT_STYLESET		0x01
#define SDL_FTFORMAT_SIZESET			0x02
#define SDL_FTFORMAT_ALPHASET		0x04
#define SDL_FTFORMAT_COLORSET		0x08
#define SDL_FTFORMAT_INDEXSET		0x10
#define SDL_FTFORMAT_NAMESET		0x20
#define SDL_FTFORMAT_EMPTY			0x40
#define SDL_FTFORMAT_END			0x80

#define SDL_FTFORMAT_STYLE_OR		0x02
#define SDL_FTFORMAT_STYLE_NAND		0x03
#define SDL_FTFORMAT_SIZESET_OFF		0x01

#define SDL_FTFORMAT_TAG			'\010'
#define SDL_FTFT_END_TAG			"\010\200"

//Font style definiton
#define SDL_FTSTYLE_NORMAL		0x00
#define SDL_FTSTYLE_BOLD		0x01
#define SDL_FTSTYLE_ITALIC		0x02
#define SDL_FTSTYLE_UNDERLINE		0x04

//PATH_MAX definition check
#ifndef PATH_MAX
# ifdef MAXPATHLEN
#  define PATH_MAX MAXPATHLEN
# else
#  define PATH_MAX 8192
# endif
#endif

#define SDL_FREETYPE_CODING_ASCII		1
#define SDL_FREETYPE_CODING_UNICODE		2
#define SDL_FREETYPE_CODING_WIDE		3

#ifndef SDL_FREETYPE_CODING
#define SDL_FREETYPE_CODING	SDL_FREETYPE_CODING_ASCII
#endif

//Structures
typedef struct {
	int		Size;
	int		Index;
	char		Name[PATH_MAX];
}
SDL_FontFaceDescription;

typedef struct SDL_GlyphCacheItem {
	void				*Next;

	int				Glyph_Index;
	FT_Bitmap			Bitmap;

	int				Bitmap_left;
	int				Bitmap_top;
	int				Advance_x;

	unsigned char			Bitmap_Data;
} SDL_GlyphCacheItem;

typedef struct SDL_FontFaceCacheItem
 {
	void			*Next;

	SDL_FontFaceDescription	FaceDescr;
	FT_Face				Face;
	SDL_GlyphCacheItem	*GlyphCache;

	//Additional font paramters - usable for style
	int			Bold_Offset;
	int			Underline_Height;

	int			Ascent;
	int			Descent;
	int			Height;
	int			LineSkip;

	int			Use_Kerning;
}
SDL_FontFaceCacheItem;

typedef struct SDL_FontChangeHist {
	void	*Next;
	Uint16	History[1];
}
SDL_FontChangeHist;

typedef struct {
	SDL_Color			Color;
	int				Alpha;
	int				Style;

	SDL_FontFaceDescription		FaceDescr;

/* Private use */
	SDL_FontFaceCacheItem		*FaceCache;
	SDL_FontChangeHist		*FontChangeHistory;
}
SDL_FontParam;

//Public funtions

extern DECLSPEC int DECLSPEC SDL_InitFreeType();
extern DECLSPEC int DECLSPEC SDL_DoneFreeType();

extern DECLSPEC char *SDL_FreeTypeGetVersion();

extern DECLSPEC int SDL_FormatTagProc(char *c, SDL_FontParam *Param, int Evidence);

extern DECLSPEC int SDL_RenderTextUNICODE(SDL_Surface *Surface, int BaseLineX, int BaseLineY, const Uint16 *Text, SDL_FontParam *ParamIn, SDL_FontParam *ParamOut);
extern DECLSPEC int SDL_RenderTextASCII(SDL_Surface *Surface, int BaseLineX, int BaseLineY, const char *Text, SDL_FontParam *ParamIn, SDL_FontParam *ParamOut);
extern DECLSPEC int SDL_RenderTextWIDE(SDL_Surface *Surface, int BaseLineX, int BaseLineY, const wchar_t *Text, SDL_FontParam *ParamIn, SDL_FontParam *ParamOut);

extern DECLSPEC int SDL_GetTextSizeUNICODE(const Uint16 *Text, SDL_FontParam *ParamIn, SDL_FontParam *ParamOut, int *Width, int *Height, int *BaselineY, int *FontLineSkip, int *FontHeight, int *Ascent, int *Descent);
extern DECLSPEC int SDL_GetTextSizeASCII(const char *Text, SDL_FontParam *ParamIn, SDL_FontParam *ParamOut, int *Width, int *Height, int *BaselineY, int *FontLineSkip, int *FontHeight, int *Ascent, int *Descent);
extern DECLSPEC int SDL_GetTextSizeWIDE(const wchar_t *Text, SDL_FontParam *ParamIn, SDL_FontParam *ParamOut, int *Width, int *Height, int *BaselineY, int *FontLineSkip, int *FontHeight, int *Ascent, int *Descent);

#if SDL_FREETYPE_CODING == SDL_FREETYPE_CODING_UNICODE
#define SDL_RenderText(a,b,c,d,e,f) SDL_RenderTextUNICODE(a,b,c,d,e,f);
#define SDL_GetTextSize(a,b,c,d,e,f,g,h,i,j) SDL_GetTextSizeUNICODE(a,b,c,d,e,f,g,h,i,j);
#endif

#if SDL_FREETYPE_CODING == SDL_FREETYPE_CODING_ASCII
#define SDL_RenderText(a,b,c,d,e,f) SDL_RenderTextASCII(a,b,c,d,e,f);
#define SDL_GetTextSize(a,b,c,d,e,f,g,h,i,j) SDL_GetTextSizeASCII(a,b,c,d,e,f,g,h,i,j);
#endif

#if SDL_FREETYPE_CODING == SDL_FREETYPE_CODING_WIDE
#define SDL_RenderText(a,b,c,d,e,f) SDL_RenderTextWIDE(a,b,c,d,e,f);
#define SDL_GetTextSize(a,b,c,d,e,f,g,h,i,j) SDL_GetTextSizeWIDE(a,b,c,d,e,f,g,h,i,j);
#endif

//Global variables
extern DECLSPEC SDL_FontParam           SDL_DefaultFont;

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif // SDL_FREETYPE_H_
