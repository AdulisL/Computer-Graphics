/***********************
Scene is the basic class handling UI.
 ***********************/
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

#include "ControlCurve.h"
#include "Curve.h"
#include "CurveShader.h"
#include "Spline.h"

#ifndef __SCENE_H__
#define __SCENE_H__

class Scene {
public:
    static int height, width; // height, width of the window
    static int oldx, oldy; // A buffer for old value of the mouse position
    
    static int mode; // 0=plain, 1=Bezier, 2=BSpline, 3=SubdivisionBezier
    
    static int resolution; // For Bezier and B-spline this is the number of edges for the curve.
    static int subdivLevel; //  For the subdivision Bezier curve, it is the level of subdivision.
    
    static ControlCurve* control; // control curve
    static Curve* curve; // the smooth spline/subdivided curve to draw
    
    static CurveShader* shader; // shader program
    Scene();
    virtual ~Scene();
    static void init();
    static void printHelp();
    
    // callback functions for UI
    static void keyboard(unsigned char key, int x, int y);
    static void reshape(int w, int h);
    static void passiveMotion(int x, int y);
    static void drag(int x, int y);
    static void mouse(int button, int state, int x, int y);
    
    static void computeCurve(); // compute curve depending on the mode
};

#endif 
