#version 130

uniform sampler2D fbo_texture;

in vec2 ex_texcoord;
out vec4 res_Color;

void main() {
    res_Color = texture2D(fbo_texture, ex_texcoord.xy);
	
	//making the background color black with this crappy if check
	if(res_Color.x < 0.01f && res_Color.y < 0.01f && res_Color.z > 0.49f && res_Color.z < 0.51f)
	{
		res_Color = vec4(0);
	}
}