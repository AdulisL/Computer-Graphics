/***********************
Spline contains the core functions for computing Bezier, BSpline and subdivision curve
 ***********************/
#include <vector>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Curve.h"
#include "ControlCurve.h"

#ifndef __SPLINE_H__
#define __SPLINE_H__


class Spline {
public:
    static void Bezier( ControlCurve* control, Curve* curve, int resolution );
    static void BSpline( ControlCurve* control, Curve* curve, int resolution );
    static void Subdiv( ControlCurve* control, Curve* curve, int subdivLevel );
};

#endif 
