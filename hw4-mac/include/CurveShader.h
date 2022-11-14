/***********************
Curve shader can display 2 curves at once.  Typically one would be the control polygon, and the other one is the spline/subdivision
 ***********************/

#include "Shader.h"

#include <vector>
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#ifndef __CURVESHADER_H__
#define __CURVESHADER_H__

#define MAX_BUFFER_SIZE 1024

class CurveShader : public Shader
{
public:
    // Curve data
    std::vector<glm::vec2> data0;
    std::vector<glm::vec2> data1;
    int n0;
    unsigned int n0_loc; // size of data0
    int n1;
    unsigned int n1_loc; // size of data1

    // Curve data as 1D textures
    GLuint texbuffer[2];
    unsigned int data0_loc; // texture sampler uniform variables
    unsigned int data1_loc;

    // Background color
    glm::vec3 backgroundcolor = glm::vec3(1.f, 1.f, 1.f);
    unsigned int backgroundcolor_loc;

    // Curve width and color
    float linewidth0 = 0.005f;
    unsigned int linewidth0_loc;
    float linewidth1 = 0.005f;
    unsigned int linewidth1_loc;
    glm::vec3 linecolor0 = glm::vec3(0.2f, 0.7f, 0.5f);
    unsigned int linecolor0_loc;
    glm::vec3 linecolor1 = glm::vec3(0.2f, 0.5f, 0.8f);
    unsigned int linecolor1_loc;

    // Marker size and color
    float markersize0 = 0.02f;
    unsigned int markersize0_loc;
    float markersize1 = 0.01f;
    unsigned int markersize1_loc;
    glm::vec3 markercolor0 = glm::vec3(0.2f, 0.7f, 0.5f);
    unsigned int markercolor0_loc;
    glm::vec3 markercolor1 = glm::vec3(0.2f, 0.5f, 0.8f);
    ;
    unsigned int markercolor1_loc;

    // Active point
    bool showActive = false;
    unsigned int showActive_loc;
    glm::vec2 activePosition;
    unsigned int activePosition_loc;
    float activeMarkerSize = 0.02f;
    unsigned int activeMarkerSize_loc;
    glm::vec3 activecolor = glm::vec3(0.f, 1.0f, 0.5f);
    unsigned int activecolor_loc;

    void initUniforms()
    { // we also initialize 1D textures here
        data0_loc = glGetUniformLocation(program, "data0");
        data1_loc = glGetUniformLocation(program, "data1");
        n0_loc = glGetUniformLocation(program, "n0");
        n1_loc = glGetUniformLocation(program, "n1");
        backgroundcolor_loc = glGetUniformLocation(program, "backgroundcolor");
        linewidth0_loc = glGetUniformLocation(program, "linewidth0");
        linewidth1_loc = glGetUniformLocation(program, "linewidth1");
        linecolor0_loc = glGetUniformLocation(program, "linecolor0");
        linecolor1_loc = glGetUniformLocation(program, "linecolor1");
        markersize0_loc = glGetUniformLocation(program, "markersize0");
        markersize1_loc = glGetUniformLocation(program, "markersize1");
        markercolor0_loc = glGetUniformLocation(program, "markercolor0");
        markercolor1_loc = glGetUniformLocation(program, "markercolor1");
        showActive_loc = glGetUniformLocation(program, "showActive");
        activePosition_loc = glGetUniformLocation(program, "activePosition");
        activeMarkerSize_loc = glGetUniformLocation(program, "activeMarkerSize");
        activecolor_loc = glGetUniformLocation(program, "activecolor");

        // For textures
        glGenTextures(2, &texbuffer[0]);
        glEnable(GL_TEXTURE_1D);
    }
    void setUniforms()
    { // and setting texture data

        n0 = glm::min(static_cast<int>(data0.size()), MAX_BUFFER_SIZE); data0.resize(MAX_BUFFER_SIZE);
        n1 = glm::min(static_cast<int>(data1.size()), MAX_BUFFER_SIZE); data1.resize(MAX_BUFFER_SIZE);

        glUniform1i(n0_loc, n0);
        glUniform1i(n1_loc, n1);
        glUniform3fv(backgroundcolor_loc, 1, &backgroundcolor[0]);
        glUniform1f(linewidth0_loc, linewidth0);
        glUniform1f(linewidth1_loc, linewidth1);
        glUniform3fv(linecolor0_loc, 1, &linecolor0[0]);
        glUniform3fv(linecolor1_loc, 1, &linecolor1[0]);
        glUniform1f(markersize0_loc, markersize0);
        glUniform1f(markersize1_loc, markersize1);
        glUniform3fv(markercolor0_loc, 1, &markercolor0[0]);
        glUniform3fv(markercolor1_loc, 1, &markercolor1[0]);
        glUniform1i(showActive_loc, showActive);
        glUniform2fv(activePosition_loc, 1, &activePosition[0]);
        glUniform1f(activeMarkerSize_loc, activeMarkerSize);
        glUniform3fv(activecolor_loc, 1, &activecolor[0]);

        // set texture data
        glBindTexture(GL_TEXTURE_1D, texbuffer[0]);
        glTexImage1D(GL_TEXTURE_1D, 0, GL_RG, GLsizei(glm::max(n0,1)), 0, GL_RG, GL_FLOAT, &data0[0][0]);
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_1D, texbuffer[1]);
        glTexImage1D(GL_TEXTURE_1D, 0, GL_RG, GLsizei(glm::max(n1,1)), 0, GL_RG, GL_FLOAT, &data1[0][0]);
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // connect texture with the shader uniform variables
        glUniform1i(data0_loc, 0);
        glUniform1i(data1_loc, 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_1D, texbuffer[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_1D, texbuffer[1]);
    }
};

#endif
