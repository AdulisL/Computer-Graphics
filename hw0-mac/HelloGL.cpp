/**Copyright Sep 23, 2022 
 * Created by Meron Asfaw
 */
#include <iostream>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
// Use of degrees is deprecated. Use radians for GLM functions
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <FreeImage.h>

static const int width = 400;
static const int height = 300;

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    glFlush();
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27: // Escape to quit
            exit(0);
            break;
    }
}

int main(int argc, char** argv)
{
    // BEGIN CREATE WINDOW
	glutInit(&argc, argv);

#ifdef __APPLE__
	glutInitDisplayMode( GLUT_3_2_CORE_PROFILE | GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
#else
    glutInitContextVersion(3,1);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
#endif
    glutInitWindowSize(width, height);
    glutCreateWindow("Hello Window");
#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    GLenum err = glewInit() ;
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    }
#endif
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    // END CREATE WINDOW
    
    std::cout << "Press ESC to quit." << std::endl;
    glClearColor (0.0, 0.2, 0.5, 1.0);
    glViewport(0,0,width,height);
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
	return 0;
}
