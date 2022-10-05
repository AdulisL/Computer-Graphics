#include <stdlib.h>
#include <iostream>
// OSX systems need their own headers
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
//#include <glm/gtc/matrix_transform.hpp>
#include "Screenshot.h"
#include "Shader.h"
#include "Square.h"

static const int width = 500;
static const int height = 500;
static const char* title = "Hello Square!";
static Square square;
class CircleShader : public Shader {
public:
    GLfloat radius = 0.2; GLuint radius_loc;
    glm::vec3 color = glm::vec3(1.0,1.0,1.0); GLuint color_loc;
    void initUniforms(){
        radius_loc = glGetUniformLocation( program, "circleradius" );
        color_loc = glGetUniformLocation( program, "circlecolor" );
    }
    void setUniforms(){
        glUniform1f(radius_loc, radius);
        glUniform3f(color_loc, color[0],color[1],color[2]);
    }
};
static CircleShader shader;

void printHelp(){
    std::cout << R"(
    Available commands:
      press 'h' to print this message again.
      press Esc to quit.
      press 'o' to save a screenshot.
)";
}

void initialize(void){
    printHelp();
    glClearColor (0.0, 0.2, 0.5, 0.0); // background color
    glViewport(0,0,width,height);

    // Initialize square
    square.init(glm::vec2(0.0,0.0), 1.0,
                glm::vec3(1.0,0.0,0.0),
                glm::vec3(1.0,1.0,0.0),
                glm::vec3(0.0,1.0,0.0),
                glm::vec3(0.0,0.0,1.0));
    // Initialize shader
    shader.read_source( "shaders/hello.vert", "shaders/hello.frag");
    shader.compile();
    glUseProgram(shader.program);
    shader.initUniforms();
    shader.setUniforms();

}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
    // BEGIN draw square
    glBindVertexArray(square.vao);
    glDrawElements(square.mode, square.count, square.type, 0 );
    // END draw square
    
    glutSwapBuffers();
    glFlush();
    
}

void saveScreenShot(void){
    int currentwidth = glutGet(GLUT_WINDOW_WIDTH);
    int currentheight = glutGet(GLUT_WINDOW_HEIGHT);
    Screenshot imag = Screenshot(currentwidth,currentheight);
    imag.save("screenshot_HelloSquare2.png");
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
        default:
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
    
    glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}
