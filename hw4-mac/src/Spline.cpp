/** Meron Asfaw
 * 11/05/2022
 */
#include "Spline.h"
#include <iostream>
#include <vector>
// Implementation of Spline::Bezier, Spline::BSpline, Spline::Subdiv.
// Each of these functions have input
//    ControlCurve* control,
//    Curve* curve,
//   and some int for resolution.
// Each function should take information from control (specifically, the
// list of point positions control->P ) and add points to the 2nd curve.
// When these functions are called, curve->P is an empty vector<vec2>.
// You may use Curve::addPoint( glm::vec2 position ) to append a new point
// position to curve.

typedef std::vector<glm::vec2> vec2s;
using namespace glm;
using namespace std;

// Some possible helper functions

// Given a list of points and t in [0,1], output Bezier point at t
glm::vec2 deCasteljau(vec2s P_in, float t){
    int n = P_in.size();
    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < n-i; j++){
            P_in[j] = mix(P_in[j], P_in[j + 1], t);
        }
    }
    return P_in[0];
}

// Given 4 points and some t in [2,3], output the BSpline point at t
glm::vec2 BSplineHelper(vec2 P1, vec2 P2, vec2 P3, vec2 P4, float t){
    float t_shift = t - 2;

    vec4 P_x(P1.x, P2.x, P3.x, P4.x);
    vec4 P_y(P1.y, P2.y, P3.y, P4.y);
    vec4 T(pow(t_shift,3), pow(t_shift,2), t_shift, 1);

    vec4 col1(-1.0/6.0, 1.0/2.0, -1.0/2.0, 1.0/6.0);
    vec4 col2(1.0/2.0, -1.0, 0.0, 2.0/3.0);
    vec4 col3(-1.0/2.0, 1.0/2.0, 1.0/2.0, 1.0/6.0);
    vec4 col4(1.0/6.0, 0.0, 0.0, 0.0);
    mat4 matrix(col1, col2, col3, col4);

    float x_result = dot(T, (matrix * P_x));
    float y_result = dot(T, (matrix * P_y));
    vec2 result = vec2(x_result, y_result);
    return result;
}

void Spline::Bezier(ControlCurve *control, Curve *curve, int resolution)
{

    for (int i = 0; i < resolution + 1; i++)
    {
        // t continuously ranges from 0 to 1
        float t = float(i) / float(resolution);

        // HW4: Your code goes here.
        curve -> addPoint(deCasteljau(control->P, t));
    }
}
// BSpline
void Spline::BSpline(ControlCurve *control, Curve *curve, int resolution)
{
    int n = control->size();
    if (n >= 4)
    { // We only do BSpline when there are at least 4 control points
        for (int i = 0; i < resolution + 1; i++)
        {
            // t continuously ranges from 1 to n-2
            float t = 1.f + float(n - 3) * float(i) / float(resolution);

            // HW4: Your code goes here
            int k = floor(t);
            if(k == n-2) { k = n - 3; }
            t = t - k + 2;

            vec2 P1 = control->P[k - 1]; // F012
            vec2 P2 = control->P[k];     // F123
            vec2 P3 = control->P[k + 1]; // F234
            vec2 P4 = control->P[k + 2]; // F345

            curve->addPoint(BSplineHelper(P1, P2, P3, P4, t));
        }
    }
}


void Spline::Subdiv(ControlCurve *control, Curve *curve, int subdivLevel)
{
    // HW4: Your code goes here
    // HW4: The result of subdivision should converge to the BSpline curve.
    //      You can design a recursion.  Or you can write for loops that subdivide
    //      the correct set of curve segments at each level.
    if(control->size() < 3) return; // protect it from breaking < 3 points
    int n = 0;
    curve->P = control->P; // copy entire control points

    for (int s = 0; s < subdivLevel; s++)
    {
        n = curve->size();
        vec2s c_p = vector<vec2>(2 * n, vec2(0.0, 0.0)); // c_p = c

        // ODD indexes of C'
        for (int k = 0; k <= n - 1; k++)
        {
            // 1. c′(2k+1) = 1/2[c(k) + c(k+1)], for k=0,...,n−1
            int odd = 2 * k + 1; // odd indexes
            c_p[odd].x = 1.0/2 * curve->P[k].x + 1.0/2 * curve->P[k + 1].x;
            c_p[odd].y = 1.0/2 * curve->P[k].y + 1.0/2 * curve->P[k + 1].y;
        }
        // EVEN indexes of C'
        for (int k = 1; k <= n - 1; k++) 
        {
            // 2. c′(2k) = 1/4[c'(2k-1) + 2c(k) + c'(2k+1)), for k=1,...,n−1
            int even = 2 * k; // even indexes
            c_p[even].x = 1.0/8 * curve->P[k - 1].x 
                     + 3.0/4 * curve->P[k].x + 1.0/8 * curve->P[k + 1].x;
            c_p[even].y = 1.0/8 * curve->P[k - 1].y 
                     + 3.0/4 * curve->P[k].y + 1.0/8 * curve->P[k + 1].y;
         }
        curve->P = vector<vec2>(c_p.begin() + 1, c_p.end() - 2);
    }
}
