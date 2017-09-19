AM_CFLAGS = -Wall -pedantic -std=c90
AM_LDFLAGS = 
LDADD = -lSDL2 -lGL -lGLEW

lib_LTLIBRARIES = libmap.la libvideo.la

libmap_la_SOURCES = map.c map.h
libmap_la_LDFLAGS = -version-info 0:0:0 $(LDADD)

libvideo_la_SOURCES = video.c video.h
libvideo_la_LDFLAGS = -version-info 0:0:0 $(LDADD)

bin_PROGRAMS = gridpathfinding gridpathfinding_static

gridpathfinding_SOURCES = main.c
gridpathfinding_LDADD = $(lib_LTLIBRARIES) $(LDADD)

gridpathfinding_static_SOURCES = main.c
gridpathfinding_static_LDADD = $(lib_LTLIBRARIES) $(LDADD)
gridpathfinding_static_LDFLAGS = -static

