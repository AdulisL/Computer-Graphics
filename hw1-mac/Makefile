CC = g++

BREWPATH = $(shell brew --prefix)
CFLAGS = -g -std=c++11 -Wno-deprecated-register -Wno-deprecated-declarations -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
INCFLAGS = -I$(BREWPATH)/include -I./include
LDFLAGS = -framework GLUT -framework OpenGL -L$(BREWPATH)/lib -lm -lfreeimage

RM = /bin/rm -f
all: Mandelbrot HelloSquare2
Mandelbrot: Mandelbrot.o Shader.o shaders/Mandelbrot.frag shaders/simple.vert
	$(CC) -o Mandelbrot Mandelbrot.o Shader.o $(LDFLAGS)
Mandelbrot.o: Mandelbrot.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c Mandelbrot.cpp 
Shader.o: src/Shader.cpp include/Shader.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Shader.cpp
clean: 
	$(RM) *.o Mandelbrot HelloSquare2

# Reproduce HW0 square	
HelloSquare2: HelloSquare2.o Shader.o shaders/hello.vert shaders/hello.frag
	$(CC) -o HelloSquare2 HelloSquare2.o Shader.o $(LDFLAGS)
HelloSquare2.o: HelloSquare2.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c HelloSquare2.cpp 
 
