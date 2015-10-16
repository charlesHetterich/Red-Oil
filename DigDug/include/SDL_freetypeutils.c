/***************************************************************************
               SDL_freetypeutils.c  -  small helper functions
                             -------------------
    begin                : Fri Aug 31 2001
    copyright            : (C) 2001 by Ales Teska
    email                : alex (at) cyber (dot) cz
 ***************************************************************************/

#include <stdlib.h>
#include "SDL_freetype.h"
#include "SDL_freetypeutils.h"

void SDL_FreeTypeError(FT_Error error)
 {
#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST  {
#define FT_ERROR_END_LIST    { -1, NULL } };
	const struct
	 {
		int		err_code;
		const char	*err_msg;
	 }
	ft_errors[] =
#include FT_ERRORS_H
	int i;

	for (i=0; ft_errors[i].err_code != -1; i++) if (ft_errors[i].err_code == error)
	 {
		SDL_SetError("FreeType error %d : %s",error,ft_errors[i].err_msg);
		return;
	 }

	SDL_SetError("FreeType : Unknown error : %d", error);
	return;
 }

//Return 0 on success / -1 on fail (Sets SDL_Errror)
int SDL_InitFreeType()
 {
	SDL_FreeTypeCheckError( FT_Init_FreeType(&SDL_FreeTypeLibrary), return(-1));

	//Preinit Char Surface
//	SDL_FreeTypeCharSurface = SDL_CreateRGBSurface(SDL_SRCALPHA , 64, 64, 32, 0xff0000, 0xff00, 0xff, 0xff000000);
//	if (SDL_FreeTypeCharSurface == NULL) return(-1);

	return(0);
 }

//Return 0 on success / -1 on fail (Sets SDL_Errror)
int SDL_DoneFreeType()
 {
#ifdef DEBUG
	int	i = 0;
	int	j = 0;
#endif

	//Purge Face cache
	while (SDL_FaceCache)
	 {
		void	*p;

		//Purge Glyph cache
		while (SDL_FaceCache->GlyphCache)
		 {
#ifdef DEBUG
			j ++;
#endif
			p = SDL_FaceCache->GlyphCache;
			SDL_FaceCache->GlyphCache = (SDL_GlyphCacheItem *) SDL_FaceCache->GlyphCache->Next;
			free(p);
		 }

		FT_Done_Face(SDL_FaceCache->Face);
		p = SDL_FaceCache;
		SDL_FaceCache = (SDL_FontFaceCacheItem *) SDL_FaceCache->Next;
		free(p);
#ifdef DEBUG
		i++;
#endif
	 }

#ifdef DEBUG
	printf("Freetype : %d font face items freed (glyph items : %d)\n",i,j);
#endif

	if (SDL_FreeTypeCharSurface != NULL) SDL_FreeSurface(SDL_FreeTypeCharSurface);

	SDL_FreeTypeCheckError(FT_Done_FreeType(SDL_FreeTypeLibrary),return(-1));

	return(0);
 }

const SDL_version *FreeType_Linked_Version() {
    static SDL_version linked_version;
    SDL_FREETYPE_VERSION(&linked_version);
    return(&linked_version);
}

char *SDL_FreeTypeGetVersion() {
    static char verstr[8];
    const SDL_version *ver = FreeType_Linked_Version();
    sprintf(verstr, "%d.%d.%d", ver->major, ver->minor, ver->patch);
    return verstr;
}

