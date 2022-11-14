/***********************
Curve is a list of 2D points
 ***********************/
#include <vector>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>


#ifndef __CURVE_H__
#define __CURVE_H__


class Curve {
public:
    std::vector<glm::vec2> P;  // vec2s list of points
    void clear(){ P.clear(); }
    void addPoint( glm::vec2 position ){
        P.push_back(position);
    }
    int size(){ return P.size(); }
};

#endif 
