/***********************
Curve is a list of 2D points
 ***********************/
#include <vector>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Curve.h"

#ifndef __CONTROL_CURVE_H__
#define __CONTROL_CURVE_H__

class ControlCurve : public Curve {
    
    
public:
    
    std::vector<glm::vec2>::iterator activePoint; // iterator pointing to the active point
    bool isactive = false;  // indicates if there is currently any active point
    float ACTIVE_RADIUS = 0.05f; // radius for detecting mouse selection
    
    void clear(){ P.clear(); isactive = false; }
    void addPoint(glm::vec2 position){
        // Add a point to the curve. To avoid misclicks, new points are added
        // only if there is no current active point.
        if (!isactive) {
            P.push_back(position);
        }
    }
    
    void deleteActivePoint(){
        // Deletes the current active point. Then resets that there is no
        // active point
        if (isactive) {
            P.erase(activePoint);
            isactive = false;
        }
    }
    
    void moveActivePoint(glm::vec2 displacement){
        // Moves the active point
        if (isactive){
            *activePoint += displacement;
        }
    }
    void updateActivePoint(glm::vec2 position){
        // Update the active point when clicking on a new one.
        // Check if the click is outside of a given radius of the current
        // active point, and if so, find the point in the neighborhood.
        // Closest point must be within the radius to be accepted.
        float dist = 1.0f;
        if (isactive){
            dist = glm::length( *activePoint - position );
        }
        if (dist > ACTIVE_RADIUS){
            isactive = false;
            // search for closest point
            for (std::vector<glm::vec2>::iterator it = P.begin();
                 it != P.end(); it++){
                dist = glm::length( *it - position );
                if (dist < ACTIVE_RADIUS){
                    activePoint = it;
                    isactive = true;
                    break;
                }
            }
        }
    }
};

#endif 
