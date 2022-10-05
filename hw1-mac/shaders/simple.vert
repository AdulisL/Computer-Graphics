# version 330 core

layout (location = 0) in vec2 pos;

out vec2 canvas_coord;

void main(){
    gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f );
    canvas_coord = pos;
}
