# version 330 core

layout (location = 0) in vec2 vtx_pos;

out vec2 pos;

void main(){
    gl_Position = vec4(vtx_pos.x, vtx_pos.y, 0.0f, 1.0f );
    pos = vtx_pos * 0.5 + 0.5; // range : [0,1] x [0,1]
}
