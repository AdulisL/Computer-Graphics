CC = g++

BREWPATH = $(shell brew --prefix)
CFLAGS = -g -std=c++11 -Wno-deprecated-register -Wno-deprecated-declarations -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
INCFLAGS = -I$(BREWPATH)/include
LDFLAGS = -framework GLUT -framework OpenGL -L$(BREWPATH)/lib -lfreeimage

RM = /bin/rm -f
all: main
main: main.o
	$(CC) -o main main.o $(LDFLAGS)
main.o: main.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
clean: 
	$(RM) *.o main

