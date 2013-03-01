#version 130

uniform sampler2D fbo_texture;

in vec2 ex_texcoord;
out vec4 res_Color;

void main() {
    res_Color = texture2D(fbo_texture, ex_texcoord.xy);
}