/***************************************************************************
                SDL_freetypeloader.c  -  RWops related functions
                             -------------------
    begin                : Sun Sep 2 2001
    copyright            : (C) 2001 by Ales Teska
    email                : alex (at) cyber (dot) cz
 ***************************************************************************/

#include <stdlib.h>
#include "SDL_freetype.h"
#include "SDL_freetypeutils.h"

static inline int SDL_RWsize(SDL_RWops *ctx)
 {
	int	curpos;
	int	size;

	curpos = SDL_RWtell(ctx);
	size = (ctx)->seek(ctx, 0, SEEK_END);
	SDL_RWseek(ctx, curpos, SEEK_SET);

	return(size);
 }

//Font name -> SDL_RWops Filter
SDL_FreeTypeLoad_Filter_t SDL_FreeTypeLoad_Filter = SDL_FreeTypeFaceLoad_FileFilter;

//Read FreeType2 - SDL convertor
unsigned long SDL_FreeTypeRead(FT_Stream stream, unsigned long offset, unsigned char *buffer, unsigned long count)
 {
	SDL_RWseek((SDL_RWops *)stream->descriptor.pointer, offset, SEEK_SET);
	if (count == 0) return(0);

	return(SDL_RWread((SDL_RWops *)stream->descriptor.pointer, buffer, 1, count));
 }

//Close FreeType2 - SDL convertor
void SDL_FreeTypeClose(FT_Stream stream)
 {
	SDL_RWclose((SDL_RWops *)stream->descriptor.pointer);
	free(stream);
 }

//Load Face
//return address of face on success/ -1 on fail
FT_Face SDL_FreeTypeFaceLoad(SDL_RWops *RWops, int Index)
 {
	FT_Face			NewFace;
	struct FT_StreamRec_	*stream;
	FT_Open_Args	args = 	{
					flags : ft_open_stream,
				};

	stream = malloc(sizeof(struct FT_StreamRec_));

	stream->base = NULL;
	stream->pos = 0;
	stream->read = SDL_FreeTypeRead;
	stream->close = SDL_FreeTypeClose;
	stream->descriptor.pointer = RWops;
	stream->memory = SDL_FreeTypeLibrary->memory;
	stream->size = SDL_RWsize(RWops);

	args.stream = stream;

	SDL_FreeTypeCheckError(FT_Open_Face(SDL_FreeTypeLibrary, &args, Index, &NewFace), return(NULL));

	return(NewFace);
 }

//From file ...
SDL_RWops *SDL_FreeTypeFaceLoad_FileFilter(const char *Name)
 {
	return(SDL_RWFromFile(Name,"rb"));
 }
