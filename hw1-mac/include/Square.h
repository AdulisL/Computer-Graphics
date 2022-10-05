/**************************************************
Square is subclass class of Geometry
that represents a 2D square.
*****************************************************/
#include "Geometry.h"
#ifndef __SQUARE_H__
#define __SQUARE_H__

class Square : public Geometry {
public:
    
    // Square without color
    void init(const glm::vec2 center, const GLfloat sidelength ){
        //
        //   pt3-----pt2
        //    |  \    |
        //    |    \  |
        //   pt0-----pt1
        //
        
        GLfloat positions[] = {
            center.x - 0.5f*sidelength, center.y - 0.5f*sidelength, // pt0
            center.x + 0.5f*sidelength, center.y - 0.5f*sidelength, // pt1
            center.x + 0.5f*sidelength, center.y + 0.5f*sidelength, // pt2
            center.x - 0.5f*sidelength, center.y + 0.5f*sidelength  // pt3
        };
        GLuint inds[] = { // vertex indices of each triangle
            0, 1, 3, // first triangle
            2, 3, 1  // second triangle
        };
        glGenVertexArrays(1, &vao );
        buffers.resize(2); // recall that buffers is std::vector<GLuint>
        glGenBuffers(2, buffers.data());
        glBindVertexArray(vao);
        
        // 0th attribute: position
        glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);
        
        // indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds), inds, GL_STATIC_DRAW);
        
        count = sizeof(inds)/sizeof(inds[0]);
        
        glBindVertexArray(0);
    }
    
    // Square with color
    void init(const glm::vec2 center, const GLfloat sidelength,
              const glm::vec3 color0, const glm::vec3 color1,
              const glm::vec3 color2, const glm::vec3 color3){
        // define square
        // color3    color2
        //   pt3-----pt2
        //    |  \    |
        //    |    \  |
        //   pt0-----pt1
        // color0    color1
        GLfloat positions[] = {
            center.x - 0.5f*sidelength, center.y - 0.5f*sidelength, // pt0
            center.x + 0.5f*sidelength, center.y - 0.5f*sidelength, // pt1
            center.x + 0.5f*sidelength, center.y + 0.5f*sidelength, // pt2
            center.x - 0.5f*sidelength, center.y + 0.5f*sidelength  // pt3
        };
        GLfloat colors[] = {
            color0[0], color0[1], color0[2],
            color1[0], color1[1], color1[2],
            color2[0], color2[1], color2[2],
            color3[0], color3[1], color3[2]
        };
        GLuint inds[] = { // vertex indices of each triangle
            0, 1, 3, // first triangle
            2, 3, 1  // second triangle
        };
        glGenVertexArrays(1, &vao );
        buffers.resize(3); // recall that buffers is std::vector<GLuint>
        glGenBuffers(3, buffers.data());
        glBindVertexArray(vao);
        
        // 0th attribute: position
        glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);
        
        // 1st attribute: color
        glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);
        
        // indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds), inds, GL_STATIC_DRAW);
        
        count = sizeof(inds)/sizeof(inds[0]);
        
        glBindVertexArray(0);
    }
};

#endif 
