#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normals;
layout(location = 2) in vec2 v_text_attributes;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;
uniform vec3 color;

// TODO: output values to fragment shader
out vec3 frag_color;
out vec3 frag_position;
out vec2 frag_text_attributes;
out vec3 frag_normals;

void main()
{	
	frag_color = color + vec3(sin(v_normals.y)/10, sin(v_normals.y)/12 * time/2, 0);
	frag_position = v_position;
	frag_text_attributes = v_text_attributes;
	frag_normals = v_normals;
	vec3 p = vec3(v_position.x * 2.5, v_position.y + sin(v_position.y*time)/5, v_position.z);
	// TODO: compute gl_Position
	gl_Position = Projection * View * Model * vec4(p, 1.0);
}