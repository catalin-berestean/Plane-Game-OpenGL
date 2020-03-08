#version 330

// TODO: get values from fragment shader

in vec3 frag_normal;
in vec3 frag_color;

out vec4 out_color;

void main()
{
	// laborator
	out_color = vec4(frag_color, 1);
}