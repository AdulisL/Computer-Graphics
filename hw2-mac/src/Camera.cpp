#include "Camera.h"
#include <math.h>

// HW2: You can add more helper functions if you want!

glm::mat3 rotation(const float degrees,const glm::vec3 axis){
    const float angle = degrees * M_PI/180.0f; // convert to radians
    
    // HW2: implement a 3D rotation matrix for the given angle and axis.
    
    return glm::mat3(1.0f); // to be replaced.
}

void Camera::rotateRight(const float degrees){
    // HW2: Update the class members "eye," "up"
}
void Camera::rotateUp(const float degrees){
    // HW2: Update the class members "eye," "up"
}
void Camera::computeMatrices(){
    // Note that glm matrix column majored.
    // That is, A[i] is the ith column of A,
    // and A_{ij} in math notation is A[j][i] in glm notation.
    
    // HW2: Update the class member "view" for the view matrix using "eye," "target," "up."
    view = glm::mat4(1.0f); // to be replaced
    
    // HW2: Update the class member "proj" for the perspective matrix using the class members "aspect," "fovy," "near," "far."
    float fovy_rad = fovy * M_PI/180.0f; // remember to convert degrees to radians.
    proj = glm::mat4(1.0f); // to be replaced
    
}

void Camera::reset(){
    eye = eye_default;// position of the eye
    target = target_default;  // look at target
    up = up_default;      // up vector
    fovy = fovy_default;  // field of view in degrees
    aspect = aspect_default; // aspect ratio
    near = near_default; // near clipping distance
    far = far_default; // far clipping distance
}