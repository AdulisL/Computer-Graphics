CC = g++

BREWPATH = $(shell brew --prefix)
CFLAGS = -g -std=c++11 -Wno-deprecated-register -Wno-deprecated-declarations -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
INCFLAGS = -I$(BREWPATH)/include
LDFLAGS = -framework GLUT -framework OpenGL -L$(BREWPATH)/lib -lfreeimage

RM = /bin/rm -f
all: HelloGL HelloSquare
HelloGL: HelloGL.o 
	$(CC) -o HelloGL HelloGL.o $(LDFLAGS)
HelloGL.o: HelloGL.cpp 
	$(CC) $(CFLAGS) $(INCFLAGS) -c HelloGL.cpp
HelloSquare: HelloSquare.o
	$(CC) -o HelloSquare HelloSquare.o $(LDFLAGS)
HelloSquare.o: HelloSquare.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c HelloSquare.cpp
clean: 
	$(RM) *.o HelloGL HelloSquare HelloSquareCopy
 
