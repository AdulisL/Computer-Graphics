/**
*   Meron Asfaw, Fall-2022
*   masfaw@ucsd.edu
*/
#version 330 core
// Inputs to the fragment shader are outputs
// of the same name of the vertex shader
in vec2 canvas_coord; // range [-1,1]x[-1,1]

uniform vec2 center;
uniform float zoom;
uniform int maxiter;

// Output the frag color
out vec4 fragColor;

// HW1: You can define customized functions here,
// e.g. complex multiplications, helper functions
// for colormap etc.

vec2 cprod(const vec2 z1, const vec2 z2){
    // (a + bi)(c+di)= a.c + a.d + bi.c + b.d(-1)
    // real = (ac - bd). imag(ad + bc)i
    // a = z1.x
    // b = z1.y
    // c = z2.x
    // d = z2.y
    float real = (z1.x * z2.x) - (z1.y * z2.y);
    float imag = (z1.x * z2.y) + (z1.y * z2.x);
    vec2 z = vec2(real, imag);
    return z;
}

void main (void){

    vec2 c = center + zoom * canvas_coord;
    // HW1: Your implementation goes here. Compute
    // the value of the Mandelbrot fractal at
    // complex number c.  Then map the value to
    // some color.
    vec2 z = vec2(0.0, 0.0);
    int I = 0;
    for (int i = 0; i < maxiter; i++){
        z = cprod(z, z) + c;
        if(length(z) > 2){
            I = i;
            break;
        } 
    }
    float color = float(float(I) / float(maxiter));
    // HW1: Replace the following default color
    // fragColor = vec4(0.5,0.5,0.5, 1.0f);
    // for(int i = 0; i <= maxiter; i++)
    fragColor = vec4(color*3,color*12,color*48, 1.0f);
}
