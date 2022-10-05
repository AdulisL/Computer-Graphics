/**************************************************
Geometry is a class for a geometric object.
It is a class that contains all informations to draw
the geometric object.
To draw an object obj of this Geometry class, we call
                                                         
  glBindVertexArray(obj.vao);
  glDrawElements(obj.mode, obj.count, obj.type, 0);
                                                         
which should explain the purpose of those class members.
Additional class members include an array of buffers and
a transformation matrix. The member buffers are convenient
during initialization, since most of the time there is a
clear buffer-geometry ownership. The memeber transf can
be utilized to encode the transformation of the object
relative to the parent frame of reference in the scene
tree.
The array of buffers is encapsulated in std::vector so
we do not need to manually allocate/free the memory for
arrays of unknown size.
You are welcomed to sub-class this Geometry class.
*****************************************************/
#include <vector>

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

class Geometry {
public:
    GLenum mode = GL_TRIANGLES; // the cookboook for glDrawElements
    int count; // number of elements to draw
    GLenum type = GL_UNSIGNED_INT; // type of the index array
    GLuint vao; // vertex array object a.k.a. geometry spreadsheet
    std::vector<GLuint> buffers; // data storage
    glm::mat4 transf = glm::mat4(1.0f); // default: identity matrix
    
    void init(){} 
    void draw(void){
        glBindVertexArray(vao);
        glDrawElements(mode,count,type,0);
    }
};

#endif 
