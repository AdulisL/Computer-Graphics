#version 330 core
in vec3 vertexcolor;
in vec2 vertexpos;

uniform float circleradius;
uniform vec3 circlecolor;

out vec4 fragColor;

void main (void){
    fragColor = vec4(vertexcolor, 1.0f);
    if (length(vertexpos)<circleradius){
        fragColor = vec4(circlecolor, 1.0f);
    }
}
