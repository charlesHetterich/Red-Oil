lib_LTLIBRARIES = libSDL_freetype.la

libSDL_freetypeincludedir = $(includedir)/SDL
libSDL_freetypeinclude_HEADERS =	\
	SDL_freetype.h

libSDL_freetype_la_SOURCES =		\
	SDL_freetype.c \
	SDL_freetypeloader.c \
	SDL_freetypeutils.c \
	SDL_freetypecoding.c

libSDL_freetype_la_LDFLAGS = 	\
	-no-undefined		\
	-release $(LT_RELEASE)	\
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

libSDL_freetype_la_LIBADD = 
