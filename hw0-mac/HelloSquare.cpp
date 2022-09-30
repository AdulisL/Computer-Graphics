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
#include "Screenshot.h"

static const int width = 500;
static const int height = 500;
static const char* title = "Hello square";
static GLuint program; // to be set as the shader program
static GLuint square_vao;
static GLuint buffers[3];
//struct Geometry {
//    GLuint vao; // geometry spreadsheet
//    unsigned int n; // number of elements to be drawn
//};
//static Geometry square;
static GLfloat myradius = 0.2;
static GLuint circleradius_loc;
static glm::vec3 mycolor = glm::vec3(1.0,1.0,1.0);
static GLuint circlecolor_loc;


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
    
    // define square
    //  blue       green
    //   pt3-----pt2
    //    |  \    |
    //    |    \  |
    //   pt0-----pt1
    // red          yellow
    GLfloat positions[] = {
        -0.5f,-0.5f, // pt0
         0.5f,-0.5f, // pt1
         0.5f, 0.5f, // pt2
        -0.5f, 0.5f  // pt3
    };
    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f, // pt0: red
        1.0f, 1.0f, 0.0f, // pt1: yellow
        0.0f, 1.0f, 0.0f, // pt2: green
        0.0f, 0.0f, 1.0f  // pt3: blue
    };
    GLuint inds[] = { // vertex indices of each triangle
        0, 1, 3, // first triangle
        2, 3, 1  // second triangle
    };
    
    
    // BEGIN of setting up the square geometry.
    
    // create 1 new geometry spreadsheet (i.e. vertex array object)
    glGenVertexArrays(1, &(square_vao));
    
    // 3 new buffers (for storing vtx positions, colors and triangle inds.)
    //GLuint buffers[3];
    glGenBuffers(3, buffers);
    
    glBindVertexArray(square_vao);  // the following written data, buffer configurations, etc., are to be remembered by the spreadsheet vao_square
    
    // write the vertex data into the buffers using the read/write machine "GL_ARRAY_BUFFER", and then set them as vertex attributes.
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]); // insert buffers[0] to GL_ARRAY_BUFFER.
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW); // key the position data into the GL_ARRAY_BUFFER machine.
    glEnableVertexAttribArray(0); // this buffer corresponds to the layout location 0 of our geometry spreadsheet; i.e. it is the 0th vertex attribute.
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0); // 0th attribute, 2 components of GL_FLOAT, no normalization, tightly packed data (no stride and offset).
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]); // insert buffers[1] to GL_ARRAY_BUFFER, which will automatically eject the previous buffers[0]
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW); // key the color data into the GL_ARRAY_BUFFER machine.
    glEnableVertexAttribArray(1);// this buffer is assigned to the 1st vertex attribute
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0); //1st attribute, 3 components of GL_FLOAT, no normalization, tightly packed data (no stride and offset).
    
    
    // Write the triangle-vertex indices to buffers[2] using the read/write machine "GL_ELEMENT_ARRAY_BUFFER"
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds), inds, GL_STATIC_DRAW);
    
    
    // unbind the vao to avoid further modification to the geometry spreadsheet.
    glBindVertexArray(0);
    // END of setting up the square geometry.
    
    
    // BEGIN writing shaders source code
    const char *vertShaderSrc =
    R"(
    # version 330 core
    layout (location = 0) in vec2 pos;
    layout (location = 1) in vec3 color;
    
    out vec3 vertexcolor;
    out vec2 vertexpos;
    
    void main(){
        gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f );
        vertexcolor = color;
        vertexpos = pos;
    }
)";
    const char *fragShaderSrc =
    R"(
    #version 330 core
    
    // Inputs to the fragment shader are outputs
    // of the same name of the vertex shader
    in vec3 vertexcolor;
    in vec2 vertexpos;
    
    uniform float circleradius;
    uniform vec3 circlecolor;
    
    // Output the frag color
    out vec4 fragColor;
    
    void main (void){
        fragColor = vec4(vertexcolor, 1.0f);
        if (length(vertexpos)<circleradius){
            fragColor = vec4(circlecolor, 1.0f);
        }
    }
)";
    // END writing shaders source code
    
    // BEGIN compiling shaders
    GLuint vs = glCreateShader(GL_VERTEX_SHADER); // The "official sheet of paper" to write the shader code
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vs, 1, &vertShaderSrc, NULL); // Write our code to vs
    glShaderSource(fs, 1, &fragShaderSrc, NULL); // and to fs
    glCompileShader(vs); // Compile shaders.
    glCompileShader(fs); // Now vs and fs are binaries.
    
    // program has been defined as a global variable
    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program); // Now vs and fs are linked, producing a program.
    glValidateProgram(program);
    glDeleteShader(vs); // clean the pre-linked intermediate binaries
    glDeleteShader(fs);
    // END compiling shaders
    
    
    // Get Uniform
    circleradius_loc = glGetUniformLocation( program, "circleradius" );
    circlecolor_loc = glGetUniformLocation( program, "circlecolor" );

    // This is the end of set up of the geometry and the shader.
    // Later, during run time (in display()) we draw the geometry by
    // binding the geometry spreadsheet (vertex array object)
    // and using the shader program.  Then we execute the "draw element"
    // command. The GPU will grab the specified geometry data,
    // execute the program, and it should produce the desired image.
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
    // BEGIN draw square
    glBindVertexArray(square_vao);
    glUseProgram(program);
    glUniform1f(circleradius_loc, myradius );
    glUniform3f(circlecolor_loc, mycolor[0], mycolor[1], mycolor[2] );
    glDrawElements(GL_TRIANGLES, // cookbook
                   6, // length of the array inds[]
                   GL_UNSIGNED_INT,
                   0
                   );
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
