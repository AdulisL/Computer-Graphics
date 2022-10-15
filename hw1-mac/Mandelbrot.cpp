#include <stdlib.h>
#include <iostream>
// OSX systems need their own headers
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
// Use of degrees is deprecated. Use radians for GLM functions
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include "Screenshot.h"
#include "Shader.h"
#include "Square.h"
#include <iomanip>

static const int width = 500;
static const int height = 500;
static const char* title = "Mandelbrot";
static Square canvas;
class MandelbrotShader : public Shader {
public:
    glm::vec2 center = glm::vec2(0.0,0.0); GLuint center_loc;
    GLfloat zoom = 2.0;                    GLuint zoom_loc;
    GLint maxiter = 50;                    GLuint maxiter_loc;
    void initUniforms(){
        center_loc = glGetUniformLocation( program, "center" );
        zoom_loc = glGetUniformLocation( program, "zoom" );
        maxiter_loc = glGetUniformLocation( program, "maxiter" );
    }
    void setUniforms(){
        glUniform2f(center_loc, center[0], center[1]);
        glUniform1f(zoom_loc, zoom);
        glUniform1i(maxiter_loc, maxiter);
    }
};
static MandelbrotShader shader;

void printHelp(){
    std::cout << R"(
    Available commands:
      press 'h' to print this message again.
      press Esc to quit.
      press 'o' to save a screenshot.
      press the arrow keys to nevigate.
      press 'a' and 'z' to zoom.
      press '+' and '-' to modify maxiter.
)";
}

void initialize(void){
    printHelp();
    glClearColor (0.0, 0.0, 0.0, 0.0); // background color
    glViewport(0,0,width,height);
    
    // Initialize canvas
    canvas.init( glm::vec2(0.,0.), 2.0f );

    // Initialize shader
    shader.read_source( "shaders/simple.vert", "shaders/Mandelbrot.frag");
    shader.compile();
    glUseProgram(shader.program);
    shader.initUniforms();
    shader.setUniforms();

}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
    // BEGIN draw square
    canvas.draw();
    // END draw square
    
    glutSwapBuffers();
    glFlush();
    
}

void saveScreenShot(void){
    int currentwidth = glutGet(GLUT_WINDOW_WIDTH);
    int currentheight = glutGet(GLUT_WINDOW_HEIGHT);
    Screenshot imag = Screenshot(currentwidth,currentheight);
    imag.save("test.png");
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27: // Escape to quit
            exit(0);
            break;
        case 'h': // print help
            printHelp();
            break;
        case 'o': // save screenshot
            saveScreenShot();
            break;
        case 'a':
            shader.zoom /= 1.1;
            shader.setUniforms();
            glutPostRedisplay();
            break;
        case 'z':
            shader.zoom *= 1.1;
            shader.setUniforms();
            glutPostRedisplay();
            break;
        case '+':
            shader.maxiter += 10;
            shader.setUniforms();
            std::cout<< "maxiter = "<<shader.maxiter<<std::endl;
            glutPostRedisplay();
            break;
        case '-':
            shader.maxiter -= 10;
            shader.setUniforms();
            std::cout<< "maxiter = "<<shader.maxiter<<std::endl;
            glutPostRedisplay();
            break;
        default:
            glutPostRedisplay();
            break;
    }
}
void specialKey(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_UP: // up
            shader.center.y += 0.1 * shader.zoom;
            shader.setUniforms();
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN: // down
            shader.center.y -= 0.1 * shader.zoom;
            shader.setUniforms();
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT: // right
            shader.center.x += 0.1 * shader.zoom;
            shader.setUniforms();
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT: // left
            shader.center.x -= 0.1 * shader.zoom;
            shader.setUniforms();
            glutPostRedisplay();
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
    glutCreateWindow(title);
#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    GLenum err = glewInit() ;
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    }
#endif
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    // END CREATE WINDOW
    
    initialize();

    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    
    glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}
