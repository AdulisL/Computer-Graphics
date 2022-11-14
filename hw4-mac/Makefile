BREWPATH = $(shell brew --prefix)

CC = g++
CFLAGS = -g -std=c++11 -Wno-deprecated-register -Wno-deprecated-declarations -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
INCFLAGS = -I./include -I$(BREWPATH)/include
LDFLAGS = -framework GLUT -framework OpenGL -L$(BREWPATH)/lib -lfreeimage

RM = /bin/rm -f
all: curves
curves: main.o Shader.o Scene.o Spline.o shaders/curve.frag
	$(CC) -o curves main.o Shader.o Scene.o Spline.o $(LDFLAGS)
main.o: main.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp 
Shader.o: src/Shader.cpp include/Shader.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Shader.cpp
Scene.o: src/Scene.cpp include/Scene.h include/CurveShader.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Scene.cpp
Spline.o: src/Spline.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Spline.cpp
clean: 
	$(RM) *.o curves
 
