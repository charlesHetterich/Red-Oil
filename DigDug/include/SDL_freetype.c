/***************************************************************************
                     SDL_freetype.c  -  core functionality
                             -------------------
    begin                : Thu Aug 30 2001
    copyright            : (C) 2001 by Ales Teska
    email                : alex (at) cyber (dot) cz
 ***************************************************************************/

#include <stdlib.h>
#include <SDL_endian.h>
#include "SDL_freetype.h"
#include "SDL_freetypeutils.h"
#include "SDL_memset4.h"

SDL_FontFaceCacheItem		*SDL_FaceCache = NULL;
FT_Library			SDL_FreeTypeLibrary;
SDL_Surface			*SDL_FreeTypeCharSurface = NULL;
SDL_FontParam			SDL_DefaultFont = {Color : {255,255,255}, Alpha : 255, Style : 0, FaceCache : NULL, FontChangeHistory : NULL,
					FaceDescr : {Size : 14, Index : 0, Name : "font.ttf"}
				 };

//Inline UNICODE strlen()
inline int SDL_FreeTypeUNICODEstrlen(Uint16 *cstr)
 {
	int	i;
	for (i=0; cstr[i] != 0; i ++);
	return(i);
 }

//Inline UNICODE character cat
inline void SDL_FreeTypeUNICODEstrcatchar(Uint16 *cstr, Uint16 c)
 {
	cstr += SDL_FreeTypeUNICODEstrlen(cstr);
	*cstr = c;
	cstr++;
	*cstr = 0;
	return;
 }

int SDL_FreeTypeFormatTagProc(Uint16 *c, SDL_FontParam *Param, int Evidence) {
	SDL_FontChangeHist	*FontChangeHist;
	Uint16			history[PATH_MAX];
	int			offset = 2;
	unsigned int		cmd;

	history[0] = UNICODE_SWAP(SDL_FTFORMAT_TAG);
	history[1] = 0;
	history[2] = 0;

	if (*c != UNICODE_SWAP(SDL_FTFORMAT_TAG)) {
		printf("Invalid format tag  : %c (%x) !", *c, *c);
		return(0);
	}

	c++;
	cmd = UNICODE_SWAP(*c) & 0xff;
	c++;

	if (cmd == SDL_FTFORMAT_END) {
		void	*p;

		if (!Evidence)
			return(offset);

		if (Param->FontChangeHistory == NULL) {
			printf("Can`t step back in font change history !");
			return(offset);
		}
		SDL_FreeTypeFormatTagProc(Param->FontChangeHistory->History, Param, 0);

		p = Param->FontChangeHistory;
		Param->FontChangeHistory = (SDL_FontChangeHist *)Param->FontChangeHistory->Next;

		free(p);
		return(offset);
	}

	if (cmd & SDL_FTFORMAT_STYLESET) {
		int	stylecmd;
		history[1] |= UNICODE_SWAP(SDL_FTFORMAT_STYLESET);
		SDL_FreeTypeUNICODEstrcatchar(history, UNICODE_SWAP(SDL_FTFORMAT_STYLESET));
		SDL_FreeTypeUNICODEstrcatchar(history, UNICODE_SWAP(Param->Style + 1));

		stylecmd = UNICODE_SWAP(*c) & 0xff;
		c++;
		offset++;

		switch (stylecmd) {
			case SDL_FTFORMAT_STYLESET : {
					Param->Style = UNICODE_SWAP(*c) - 1;
					break;
				}

			case SDL_FTFORMAT_STYLE_OR : {
					Param->Style |= UNICODE_SWAP(*c) - 1;
					break;
				}

			case SDL_FTFORMAT_STYLE_NAND : {
					Param->Style &= ~(UNICODE_SWAP(*c) - 1);
					break;
				}

			default:
				//Warning
				printf("Unknown style set action %d !", stylecmd);
		}

		c++;
		offset++;
	}

	if (cmd & SDL_FTFORMAT_SIZESET) {
		int	sizecmd;
		history[1] |= UNICODE_SWAP(SDL_FTFORMAT_SIZESET);
		SDL_FreeTypeUNICODEstrcatchar(history, UNICODE_SWAP(SDL_FTFORMAT_SIZESET));
		SDL_FreeTypeUNICODEstrcatchar(history, UNICODE_SWAP(Param->FaceDescr.Size));

		sizecmd = UNICODE_SWAP(*c) & 0xff;
		c++;
		offset++;

		switch (sizecmd) {
			case SDL_FTFORMAT_SIZESET : {
					Param->FaceDescr.Size = UNICODE_SWAP(*c);
					break;
				}

			case SDL_FTFORMAT_SIZESET_OFF : {
					Param->FaceDescr.Size += UNICODE_SWAP(*c);
					break;
				}

			default:
				/*Warning*/ printf("Unknown size set action %d !", sizecmd);
		}

		c++;
		offset++;
	}

	if (cmd & SDL_FTFORMAT_ALPHASET) {
		history[1] |= UNICODE_SWAP(SDL_FTFORMAT_ALPHASET);
		SDL_FreeTypeUNICODEstrcatchar(history, UNICODE_SWAP(Param->Alpha));

		Param->Alpha = UNICODE_SWAP(*c) & 0xff;
		if (Param->Alpha == 1)
			Param->Alpha = 0;

		c++;
		offset++;
	}

	if (cmd & SDL_FTFORMAT_COLORSET) {
		history[1] |= UNICODE_SWAP(SDL_FTFORMAT_COLORSET);
		SDL_FreeTypeUNICODEstrcatchar(history, UNICODE_SWAP((Param->Color.r == 0) ? 1 : Param->Color.r));
		SDL_FreeTypeUNICODEstrcatchar(history, UNICODE_SWAP((Param->Color.g == 0) ? 1 : Param->Color.g));
		SDL_FreeTypeUNICODEstrcatchar(history, UNICODE_SWAP((Param->Color.b == 0) ? 1 : Param->Color.b));

		Param->Color.r = UNICODE_SWAP(*c) & 0xff;
		c++;
		offset++;

		Param->Color.g = UNICODE_SWAP(*c) & 0xff;
		c++;
		offset++;

		Param->Color.b = UNICODE_SWAP(*c) & 0xff;
		c++;
		offset++;
	}

	if (cmd & SDL_FTFORMAT_INDEXSET) {
		history[1] |= UNICODE_SWAP(SDL_FTFORMAT_INDEXSET);
		SDL_FreeTypeUNICODEstrcatchar(history, UNICODE_SWAP(Param->FaceDescr.Index + 1));

		Param->FaceDescr.Index = (UNICODE_SWAP(*c) & 0xff) - 1;

		c++;
		offset++;
	}

	if (cmd & SDL_FTFORMAT_NAMESET) {
		char	*c1;
		int	i,j;

		history[1] |= UNICODE_SWAP(SDL_FTFORMAT_NAMESET);
		j = SDL_FreeTypeUNICODEstrlen(history);
		for (i=0;Param->FaceDescr.Name[i] != 0; i++) history[i+j] = UNICODE_SWAP(Param->FaceDescr.Name[i]);
		history[j+i] = UNICODE_SWAP('\001');
		history[j+i+1] = 0;

		c1 = Param->FaceDescr.Name;

		while (*c != UNICODE_SWAP('\001'))
		 {
			*c1 = (char)UNICODE_SWAP(*c);

			c1++;
			c++;
			offset++;
		 }
		*c1 = 0;

		c++;
		offset++;
	}

	//Add font change to the history
	if (Evidence == 1) {
		FontChangeHist = (SDL_FontChangeHist *) malloc(sizeof(SDL_FontChangeHist) + (SDL_FreeTypeUNICODEstrlen(history) * sizeof(Uint16)));
		memcpy(FontChangeHist->History, history, SDL_FreeTypeUNICODEstrlen(history) * sizeof(Uint16));
		FontChangeHist->Next = Param->FontChangeHistory;
		Param->FontChangeHistory = FontChangeHist;
	}

	return(offset);
}

int SDL_FreeTypeClearFontChangeHistory(SDL_FontParam *Param) {
	int	i = 0;

	while (Param->FontChangeHistory != NULL) {
		void	*p;
		i++;

		p = Param->FontChangeHistory;
		Param->FontChangeHistory = (SDL_FontChangeHist *)Param->FontChangeHistory->Next;
		free(p);
	}

	return(i);
}

//Searching font in cache
//return 0 on success/ -1 on fail
int SDL_FreeTypeGetFontFace(SDL_FontParam *Param) {
	SDL_FontFaceCacheItem	*CacheItem;

	//TO-DO : Better font cache searching
	for (CacheItem = (SDL_FontFaceCacheItem *) SDL_FaceCache; CacheItem; CacheItem = (SDL_FontFaceCacheItem *)CacheItem->Next)
		if (memcmp(&CacheItem->FaceDescr, &Param->FaceDescr, sizeof(SDL_FontFaceDescription)) == 0) {
			Param->FaceCache = CacheItem;
			return(0);
		}

	//Make new cache item ...
	CacheItem = (SDL_FontFaceCacheItem *) malloc(sizeof(SDL_FontFaceCacheItem));

	CacheItem->FaceDescr = Param->FaceDescr;
	CacheItem->GlyphCache = NULL;

	//Load new face ...
	CacheItem->Face = SDL_FreeTypeFaceLoad(SDL_FreeTypeLoad_Filter(Param->FaceDescr.Name), Param->FaceDescr.Index);
	if (CacheItem->Face == NULL)
	 {
		free(CacheItem);
		return(-1);
	 }

	//Make sure that our font face is scalable (global metrics)
	if ( ! FT_IS_SCALABLE(CacheItem->Face) ) {
		/*Warning*/ printf("Font %s is not scalable !", Param->FaceDescr.Name);
		FT_Done_Face(CacheItem->Face);
		free(CacheItem);
		return(-1);
	}

	//Set the character size and use default DPI (72)
	SDL_FreeTypeCheckError(FT_Set_Char_Size(CacheItem->Face, 0, Param->FaceDescr.Size * 64, 0, 0), FT_Done_Face(CacheItem->Face); free(CacheItem); return(-1));

	//Fill the parameters
	//TO-DO : Inspect this
	CacheItem->Bold_Offset = 1 + Param->FaceDescr.Size / 20;
	CacheItem->Underline_Height = FT_FLOOR(FT_MulFix(CacheItem->Face->underline_thickness, CacheItem->Face->size->metrics.y_scale));
	if ( CacheItem->Underline_Height < 1 )
		CacheItem->Underline_Height = 1;

	CacheItem->Ascent = FT_CEIL(FT_MulFix(CacheItem->Face->bbox.yMax, CacheItem->Face->size->metrics.y_scale));
	CacheItem->Descent  = FT_CEIL(FT_MulFix(CacheItem->Face->bbox.yMin, CacheItem->Face->size->metrics.y_scale));
	CacheItem->Height = CacheItem->Ascent - CacheItem->Descent + 1;
	CacheItem->LineSkip = FT_CEIL(FT_MulFix(CacheItem->Face->height, CacheItem->Face->size->metrics.y_scale));
	CacheItem->Use_Kerning = FT_HAS_KERNING(CacheItem->Face);

	//Insert cache item into cache
	CacheItem->Next = SDL_FaceCache;
	SDL_FaceCache = CacheItem;

	Param->FaceCache = CacheItem;

	return(0);
}

SDL_GlyphCacheItem *SDL_FreeTypeGetGlyph(SDL_FontParam *Param, int glyph_index) {
	SDL_GlyphCacheItem *GlyphCacheItem;

	for (GlyphCacheItem = (SDL_GlyphCacheItem *) Param->FaceCache->GlyphCache;GlyphCacheItem;GlyphCacheItem = (SDL_GlyphCacheItem *) GlyphCacheItem->Next)
		if (GlyphCacheItem->Glyph_Index == glyph_index)
			return(GlyphCacheItem);

	if (FT_Load_Glyph(Param->FaceCache->Face, glyph_index, FT_LOAD_RENDER ))
		return(NULL);

	GlyphCacheItem = (SDL_GlyphCacheItem *) malloc(sizeof(SDL_GlyphCacheItem) + (Param->FaceCache->Face->glyph->bitmap.pitch * Param->FaceCache->Face->glyph->bitmap.rows));

	GlyphCacheItem->Glyph_Index = glyph_index;
	GlyphCacheItem->Bitmap = Param->FaceCache->Face->glyph->bitmap;
	GlyphCacheItem->Bitmap_left = Param->FaceCache->Face->glyph->bitmap_left;
	GlyphCacheItem->Bitmap_top = Param->FaceCache->Face->glyph->bitmap_top;
	GlyphCacheItem->Advance_x = FT_CEIL(Param->FaceCache->Face->glyph->metrics.horiAdvance);
	memcpy(&GlyphCacheItem->Bitmap_Data, Param->FaceCache->Face->glyph->bitmap.buffer, (Param->FaceCache->Face->glyph->bitmap.pitch * Param->FaceCache->Face->glyph->bitmap.rows));
	GlyphCacheItem->Bitmap.buffer = &GlyphCacheItem->Bitmap_Data;

	GlyphCacheItem->Next = Param->FaceCache->GlyphCache;
	Param->FaceCache->GlyphCache = GlyphCacheItem;

	return(GlyphCacheItem);
}

inline int SDL_FreeTypeBlitFTBitmap(SDL_Surface *Surface, FT_Bitmap *Bitmap, int PosX, int PosY, SDL_FontParam *Param) {
	Uint8		*raw_pixels;
	SDL_Rect	TargetPos;
	SDL_Rect	SourcePos;
	int		i;
	SDL_Rect	*ClipRect = &Surface->clip_rect;

	if (Param->Alpha == 0)
		return(0);

	TargetPos.x = PosX;
	TargetPos.y = PosY;

	//Italic font is widther than normal
	i = Bitmap->width;
	if (Param->Style & SDL_FTSTYLE_ITALIC)
		i += (int)(Bitmap->rows * SDL_FT_FITALIC_ANGLE);

	//There is no need to draw
	if ((TargetPos.x > (ClipRect->x + ClipRect->w)) || (TargetPos.y > (ClipRect->y +ClipRect->h )) || ((TargetPos.y+Bitmap->rows) < ClipRect->y) || ((TargetPos.x+i) < ClipRect->x))
		return(0);

	//Is CharSurface big enough ??
	if (SDL_FreeTypeCharSurface != NULL) {
		if ((SDL_FreeTypeCharSurface->w < i)||(SDL_FreeTypeCharSurface->h < Bitmap->rows)) {
			SDL_FreeSurface(SDL_FreeTypeCharSurface);
			SDL_FreeTypeCharSurface = NULL;
		}
	}

	SourcePos.x = 0;
	SourcePos.y = 0;
	SourcePos.w = Bitmap->width;
	SourcePos.h = Bitmap->rows;
	if (Param->Style & SDL_FTSTYLE_ITALIC) SourcePos.w += Bitmap->rows * SDL_FT_FITALIC_ANGLE;

	if (SDL_FreeTypeCharSurface == NULL) {
		SDL_FreeTypeCharSurface = SDL_CreateRGBSurface(SDL_SRCALPHA , i, Bitmap->rows, 32, 0xff000000, 0xff0000, 0xff00, 0xff);
		if (SDL_FreeTypeCharSurface == NULL) {
			/*Warning*/ printf("Can`t get char surface : %s",SDL_GetError());
			return(-1);
		}
	}	
	

	//Clipping
	if ((TargetPos.x + SourcePos.w) > (ClipRect->x + ClipRect->w))
		SourcePos.w = ClipRect->w - (TargetPos.x - ClipRect->x);
	if ((TargetPos.y + SourcePos.h) > (ClipRect->y + ClipRect->h))
		SourcePos.h = ClipRect->h - (TargetPos.y - ClipRect->y);

	if (TargetPos.x < ClipRect->x) {
		int	delta;

		delta = ClipRect->x - TargetPos.x;
		SourcePos.w -= delta;
		TargetPos.x += delta;
		SourcePos.x += delta;
	}

	if (TargetPos.y < ClipRect->y) {
		int	delta;

		delta = ClipRect->y - TargetPos.y;
		SourcePos.h -= delta;
		TargetPos.y += delta;
		SourcePos.y += delta;
	}

	raw_pixels = (Uint8 *) SDL_FreeTypeCharSurface->pixels;

	//Fill temporary surface with text color and full-transparency
	for (i = 0; i < SourcePos.h; i++ , raw_pixels += SDL_FreeTypeCharSurface->pitch) SDL_memset4(raw_pixels, SDL_MapRGBA(SDL_FreeTypeCharSurface->format, Param->Color.r, Param->Color.g, Param->Color.b,0), SourcePos.w);

	raw_pixels = (Uint8 *) SDL_FreeTypeCharSurface->pixels;

	switch (Bitmap->pixel_mode) {
		case ft_pixel_mode_grays: {
				Uint8		*SrcPix = Bitmap->buffer;
				register	int	x,y;

				//Move to alpha position
				raw_pixels += SDL_FreeTypeCharSurface->format->Ashift >> 3;

				if (Param->Style & SDL_FTSTYLE_ITALIC)
				 {
					double ioffset = Bitmap->rows * SDL_FT_FITALIC_ANGLE;

					if (Param->Alpha == 255)
					 {
						//No alpha
						for (y = 0; y < Bitmap->rows; y++, SrcPix += Bitmap->pitch, ioffset -= SDL_FT_FITALIC_ANGLE)
						 {
							register int Sub = ((int)(ioffset));

             	                                                     	for (x = 0; x <  Bitmap->width; x++) raw_pixels[(x + Sub) << 2] = *(SrcPix + x);
							raw_pixels += SDL_FreeTypeCharSurface->pitch;
						 }
					 } else    //Alpha
						for (y = 0; y < Bitmap->rows; y++, SrcPix += Bitmap->pitch, ioffset -= SDL_FT_FITALIC_ANGLE)
						 {
							register int Sub = ((int)(ioffset));

             	                                                     	for (x = 0; x <  Bitmap->width; x++) raw_pixels[(x + Sub) << 2] = (*(SrcPix + x) * Param->Alpha) >> 8;
							raw_pixels += SDL_FreeTypeCharSurface->pitch;
						 }
				 } else if (Param->Alpha == 255)
					 {
						//No alpha ...
						for (y = 0; y < Bitmap->rows; y++, SrcPix += Bitmap->pitch)
						 {
							for (x = 0; x <  Bitmap->width; x++) raw_pixels[x << 2] = *(SrcPix + x);
							raw_pixels += SDL_FreeTypeCharSurface->pitch;
						 }
					  } else {
						//Alpha ...
						for (y = 0; y < Bitmap->rows; y++, SrcPix += Bitmap->pitch)
						 {
							for (x = 0; x <  Bitmap->width; x++) raw_pixels[x << 2] = (*(SrcPix + x) * Param->Alpha) >> 8;
							raw_pixels += SDL_FreeTypeCharSurface->pitch;
						 }

					  }

				break;
			}

		default:
			/*Warning*/ printf("Unknown pixel type in font !");
			return(-1);
	}

	// Final blit
	SDL_BlitSurface(SDL_FreeTypeCharSurface, &SourcePos, Surface, &TargetPos);

	//BOLD
	if (Param->Style & SDL_FTSTYLE_BOLD)
	 {
		//TO-DO : Here TargetPos can be broken
		SDL_Rect BoldTarget = TargetPos;

		BoldTarget.x += Param->FaceCache->Bold_Offset;
		SDL_BlitSurface(SDL_FreeTypeCharSurface, &SourcePos, Surface, &BoldTarget);
	 }

	return(0);
}

//int SDL_RenderTextUTF8(SDL_Surface *Surface, int BaseLineX, int BaseLineY, const char *Text, SDL_FontParam *ParamIn, SDL_FontParam *ParamOut) {
// }

int SDL_RenderTextUNICODE(SDL_Surface *Surface, int BaseLineX, int BaseLineY, const Uint16 *Text, SDL_FontParam *ParamIn, SDL_FontParam *ParamOut) {
	SDL_FontParam	CurParam;
	Uint16		*cpos;
	FT_UInt		previous = 0;

	//Set current font parameters
	CurParam = *ParamIn;

	//Go thu text and draw characters
	for (cpos = (Uint16 *)Text;*cpos != 0; cpos++) {
		int			glyph_index;
		SDL_GlyphCacheItem	*Glyph;
		int			OldBaseLineX = BaseLineX;
		Uint16			c;

		//Process format char
		while (*cpos == UNICODE_SWAP(SDL_FTFORMAT_TAG))
			cpos += SDL_FreeTypeFormatTagProc(cpos, &CurParam, 1);

		c = UNICODE_SWAP(*cpos);

		if (c == 0)
			break;

		//Skip drawing we go non-printable char
		if (c<32)
			continue;

		//Check FontFace Cache consistecy
		if (CurParam.FaceCache != NULL)
			if (memcmp(&CurParam.FaceCache->FaceDescr, &CurParam.FaceDescr, sizeof(SDL_FontFaceDescription)) != 0)
				CurParam.FaceCache = NULL;

		//Get correct font face
		if (CurParam.FaceCache == NULL) {
			SDL_FreeTypeGetFontFace(&CurParam);

			//If there is some problem use default font
			if (CurParam.FaceCache == NULL) {
				//TO-DO : Default font - better copy (without history ...)!!!
				/*Warning*/ printf("Can`t find font %s - using default\n", CurParam.FaceDescr.Name);
				CurParam = SDL_DefaultFont;

				if (CurParam.FaceCache == NULL) {
					SDL_FreeTypeGetFontFace(&CurParam);

					if (CurParam.FaceCache == NULL) {
						/*Error*/ printf("Permanent font error !\n");

						return(-1);
					}
				}
			}
		}

		//Get glyph index
		glyph_index = FT_Get_Char_Index(CurParam.FaceCache->Face, c);

		//Make space between characters == kerneling
		if ( CurParam.FaceCache->Use_Kerning && previous && glyph_index ) {
			FT_Vector  delta;

			FT_Get_Kerning(CurParam.FaceCache->Face, previous, glyph_index, ft_kerning_default, &delta );
			BaseLineX += delta.x >> 6;
		}
		previous = glyph_index;

		//Get glyph bitmap
		Glyph = SDL_FreeTypeGetGlyph(&CurParam, glyph_index);

		if (Glyph != NULL) {
			//Blit glyph bitmap into the surface
			if (c != ' ') SDL_FreeTypeBlitFTBitmap(Surface, &Glyph->Bitmap, BaseLineX + Glyph->Bitmap_left, BaseLineY - Glyph->Bitmap_top, &CurParam);

			BaseLineX += Glyph->Advance_x;
			if (CurParam.Style & SDL_FTSTYLE_BOLD)
				BaseLineX += CurParam.FaceCache->Bold_Offset;
		}

		//UNDERLINE
		//TO-DO : Underline is not transparent !!!! (Fill must be replaced by Blit)
		if (CurParam.Style & SDL_FTSTYLE_UNDERLINE) {
			SDL_Rect	und_rect;

			und_rect.x = OldBaseLineX;
			und_rect.y = BaseLineY;
			und_rect.h = CurParam.FaceCache->Underline_Height;
			und_rect.w = BaseLineX - OldBaseLineX;

			SDL_FillRect(Surface, &und_rect, SDL_MapRGB(Surface->format, CurParam.Color.r, CurParam.Color.g, CurParam.Color.b));
		}
	}

	//Copy current font parametrs to the caller space (if he wants to)
	if (ParamOut != NULL)
		*ParamOut = CurParam;
	else {
		int i =	SDL_FreeTypeClearFontChangeHistory(&CurParam);
		if (i != 0) ///*Warning*/ printf("Invalid font change tagging - %d unended tag(s) !",i);
			printf("Invalid font change tagging - %d unended tag(s) !\n",i);
	}

	return(0);
}

int SDL_GetTextSizeUNICODE(const Uint16 *Text, SDL_FontParam *ParamIn, SDL_FontParam *ParamOut, int *Width, int *Height, int *BaselineY, int *FontLineSkip, int *FontHeight, int *Ascent, int *Descent)
 {
	SDL_FontParam	CurParam;
	FT_UInt		previous = 0;
	Uint16 		*cpos;
	int		BaseLineX = 0;
	int		preBaseLineY = 0;
	int		MaxY = 0;

	int		preFontHeight = 0;
	int		preLineSkip = 0;
	int		preAscent = 0;
	int		preDescent = 0;

	//Set current font parameters
	CurParam = *ParamIn;

	//Initial parametrs check
	if (CurParam.FaceCache != NULL) {
		if (preFontHeight < CurParam.FaceCache->Height)
			preFontHeight = CurParam.FaceCache->Height;
		if (preLineSkip < CurParam.FaceCache->LineSkip)
			preLineSkip = CurParam.FaceCache->LineSkip;
		if (preAscent < CurParam.FaceCache->Ascent)
			preAscent = CurParam.FaceCache->Ascent;
		if (preDescent > CurParam.FaceCache->Descent)
			preDescent = CurParam.FaceCache->Descent;
	}

	//Go thu text and get sizes of the characters
	for (cpos = (Uint16 *) Text;*cpos != 0; cpos++)
	 {
		int			glyph_index;
		SDL_GlyphCacheItem	*Glyph;
		Uint16			c;

		//Process format char
		while (*cpos == UNICODE_SWAP(SDL_FTFORMAT_TAG))
			cpos += SDL_FreeTypeFormatTagProc(cpos, &CurParam, 1);

		c = UNICODE_SWAP(*cpos);

		if (c == 0)
			break;

		//Skip non-printable char
		if (c<32)
			continue;

		//Check FontFace Cache consistecy
		if (CurParam.FaceCache != NULL)
			if (memcmp(&CurParam.FaceCache->FaceDescr, &CurParam.FaceDescr, sizeof(SDL_FontFaceDescription)) != 0)
				CurParam.FaceCache = NULL;

		//Get correct font face
		if (CurParam.FaceCache == NULL)
		 {
			SDL_FreeTypeGetFontFace(&CurParam);

			//If there is some problem use default font
			if (CurParam.FaceCache == NULL)
			 {
				//TO-DO : Default font !!!
				/*Warning*/ printf("Can`t find font %s - using default", CurParam.FaceDescr.Name);
				CurParam = SDL_DefaultFont;

				if (CurParam.FaceCache == NULL) {
					SDL_FreeTypeGetFontFace(&CurParam);

					if (CurParam.FaceCache == NULL) {
						/*Error*/ printf("Permanent font error !");
						return(-1);
					}
				}
			}

			if (preFontHeight < CurParam.FaceCache->Height)
				preFontHeight = CurParam.FaceCache->Height;
			if (preLineSkip < CurParam.FaceCache->LineSkip)
				preLineSkip = CurParam.FaceCache->LineSkip;
			if (preAscent < CurParam.FaceCache->Ascent)
				preAscent = CurParam.FaceCache->Ascent;
			if (preDescent > CurParam.FaceCache->Descent)
				preDescent = CurParam.FaceCache->Descent;
		}

		//Get glyph index
		glyph_index = FT_Get_Char_Index(CurParam.FaceCache->Face, c);

		//Make space between characters == kerneling
		if ( CurParam.FaceCache->Use_Kerning && previous && glyph_index ) {
			FT_Vector  delta;

			FT_Get_Kerning(CurParam.FaceCache->Face, previous, glyph_index, ft_kerning_default, &delta );
			BaseLineX += delta.x >> 6;
		}
		previous = glyph_index;

		//Get glyph bitmap
		Glyph = SDL_FreeTypeGetGlyph(&CurParam, glyph_index);
		if (Glyph != NULL) {
			if (preBaseLineY < Glyph->Bitmap_top)
				preBaseLineY = Glyph->Bitmap_top;
			if (MaxY < Glyph->Bitmap.rows)
				MaxY = Glyph->Bitmap.rows;

			BaseLineX += Glyph->Advance_x;
			if (CurParam.Style & SDL_FTSTYLE_BOLD)
				BaseLineX += CurParam.FaceCache->Bold_Offset;
		}

	}

	if (ParamOut != NULL)
		*ParamOut = CurParam;
	else {
		int i =	SDL_FreeTypeClearFontChangeHistory(&CurParam);
		if (i != 0) ///*Warning*/ printf("Invalid font change tagging - %d unended tag(s) !",i);
			printf("Invalid font change tagging - %d unended tag(s) !\n",i);
	}

	if (Height != NULL)
		*Height = MaxY;
	if (Width != NULL)
		*Width = BaseLineX;
	if (BaselineY!= NULL)
		*BaselineY = preBaseLineY;
	if (FontLineSkip!= NULL)
		*FontLineSkip = preLineSkip;
	if (FontHeight != NULL)
		*FontHeight = preFontHeight;
	if (Ascent != NULL)
		*Ascent = preAscent;
	if (Descent != NULL)
		*Descent = preDescent;

	return(0);
}
