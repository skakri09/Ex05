#version 130

in vec4 in_Position;
out vec2 uv_coords;

void main() {
	gl_Position = vec4(in_Position.xy, 0.0, 1.0);
	uv_coords = in_Position.zw;
}