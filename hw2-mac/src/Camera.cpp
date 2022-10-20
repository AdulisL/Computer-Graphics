#include "Camera.h"
#include <math.h>

// HW2: You can add more helper functions if you want!
using namespace glm;

glm::mat3 transpose(mat3 input){
    // mat3[col][row] accessing
    vec3 col0(input[0][0], input[1][0], input[2][0]); 
    vec3 col1(input[0][1], input[1][1], input[2][1]);
    vec3 col2(input[0][2], input[1][2], input[2][2]);

    mat3 result(col0, col1, col2); // transpose
    return result;
}
glm::mat3 crossMatrix(vec3 a){
    vec3 col0(0.f, a.z, -(a.y)); // [0, a_z, -a_y]
    vec3 col1(-(a.z), 0.f, a.x); // [-a_z, 0, a_x]
    vec3 col2(a.y, -(a.x), 0);   // [a_y, -a_x, 0]
    mat3 temp(0.f, -a.z, a.y,
              a.z, 0.f, -a.x,
              -a.y, a.x, 0.f);
    // temp = transpose(temp);
    mat3 result(col0, col1, col2);

    // return temp;
    return result;
}

glm::mat3 rotation(const float degrees, const glm::vec3 axis)
{
    const float angle = degrees * M_PI/180.0f; // convert to radians
    vec3 a = glm::normalize(axis);
    // HW2: implement a 3D rotation matrix for the given angle and axis.
    mat3 aCrossed = crossMatrix(a);
    mat3 aaTranspose = glm::outerProduct(a, a); // [aaT]
    float cosAngle = glm::cos(angle);
    float sinAngle = glm::sin(angle);
    

    mat3 Idmatrix(1.0f); // Identity matrix
    // R = cosø.I + (1 - cosØ)aaT + sinØ.[ax]
    mat3 cosIdentity((Idmatrix * cosAngle));               // cosø.I
    mat3 cosTransposed((1 - cosAngle) * aaTranspose);       // (1 - cosØ)aaT
    mat3 sinCrossed(sinAngle * aCrossed);                   // sinØ.[ax]
    mat3 result = cosIdentity + cosTransposed + sinCrossed; // Ra,Ø
    return result; // to be replaced.
}
// helper function
glm::vec3 computeAbsolute(vec3 u, vec3 v){
    vec3 top(u - v); // (u - v)
    float bottom = sqrt(u.x * u.y *u.z - v.x * v.y * v.z); // |u - v|
    vec3 result = top / bottom; 
    return result;
}
glm::vec3 crossProduct(vec3 u, vec3 v){
    float row0 = (u.y * v.z) - (u.z * v.y);
    float row1 = (u.z * v.x) - (u.x * v.z);
    float row2 = (u.x * v.y) - (u.y * v.x);
    vec3 result(row0, row1, row2);
    return result;
}
void Camera::rotateRight(const float degrees){
    // HW2: Update the class members "eye," "up"
    // const float angle = degrees * M_PI/180.0f; // convert to radians
    vec3 bigEye = eye - target;
    vec3 c3 = glm::normalize(bigEye);
    vec3 c2 = up - glm::dot(c3, up)*c3;
    up = glm::normalize(c2);
    // vec3 c1 = cross(c2, c3);

    vec3 rotateEye = rotation(degrees, up)*bigEye;
    eye = rotateEye + target;
}

void Camera::rotateUp(const float degrees){
    // HW2: Update the class members "eye," "up"
    vec3 bigEye = eye - target;
    vec3 c3 = glm::normalize(bigEye);        // z vector
    // vec2 c2 = up - glm::dot(c3, up) * c3;    // y vector
    up = up - glm::dot(c3, up) * c3;
    up = glm::normalize(up);

    vec3 rotateC2 = rotation(90, c3) * up;     // y vector rotate clockwise 90
    rotateC2 = normalize(rotateC2);
    vec3 rotateEye = rotation(degrees, rotateC2) * bigEye; // shifting
    eye = rotateEye + target;

    vec3 rotateUp = rotation(degrees, rotateC2) * up;
    up = normalize(rotateUp);
}
void Camera::computeMatrices(){
    // Note that glm matrix column majored.
    // That is, A[i] is the ith column of A,
    // and A_{ij} in math notation is A[j][i] in glm notation.
    vec3 bigEye = eye - target;         // view vector position
    vec3 c3 = normalize(bigEye);        // z vector
    vec3 c2 = up - dot(c3, up) * c3;    // y vector
    c2 = glm::normalize(c2);
    vec3 c1 = glm::cross(c2, c3);       // [y x z]

    glm::mat4 C = glm::mat4(c1.x, c1.y, c1.z, 0.0f,   // C[col][row]
                            c2.x, c2.y, c2.z, 0.0f,
                            c3.x, c3.y, c3.z, 0.0f,
                            eye.x, eye.y, eye.z, 1.0f );
    view = glm::inverse(C); // to be replaced

    // HW2: Update the class member "proj" for the perspective matrix using the class members "aspect," "fovy," "near," "far."
    float fovy_rad = fovy * M_PI/180.0f; // remember to convert degrees to radians.
    float func1 = 1 / (aspect * tan(fovy_rad / 2.0f));
    float func2 = 1 / tan(fovy_rad / 2.0f);
    float func3 = -((far+near) / (far-near));
    float func4 = -((2*far*near) / (far-near));

    proj = glm::mat4(func1, 0.f, 0.f, 0.f,
                     0.f, func2, 0.f, 0.f,
                     0.f, 0.f, func3, -1.0f,
                     0.f, 0.f, func4, 0.f); // to be replaced
}

void Camera::reset(){
    eye = eye_default;// position of the eye
    target = target_default;  // look at target
    up = up_default;      // up vector
    fovy = fovy_default;  // field of view in degrees
    aspect = aspect_default; // aspect ratio (a)
    near = near_default; // near clipping distance
    far = far_default; // far clipping distance
}