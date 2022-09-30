CC = g++

BREWPATH = $(shell brew --prefix)
CFLAGS = -g -std=c++11 -Wno-deprecated-register -Wno-deprecated-declarations -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
INCFLAGS = -I$(BREWPATH)/include
LDFLAGS = -framework GLUT -framework OpenGL -L$(BREWPATH)/lib -lfreeimage

RM = /bin/rm -f
all: HelloSquareCopy
HelloSquareCopy: HelloSquareCopy.o
	$(CC) -o HelloSquareCopy HelloSquareCopy.o $(LDFLAGS)
HelloSquareCopy.o: HelloSquareCopy.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c HelloSquareCopy.cpp
clean: 
	$(RM) *.o HelloSquareCopy

