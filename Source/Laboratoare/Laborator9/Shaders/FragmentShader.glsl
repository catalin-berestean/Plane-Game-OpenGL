#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;


in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texture_coord;
in vec3 frag_color;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	
	out_color = vec4(frag_color, 1);
	out_color = vec4(frag_normal, 1);

	out_color = vec4(1);
}