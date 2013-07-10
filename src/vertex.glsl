#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 data;
uniform mat4 MVP;

void main()
{
	vec4 t = vec4(position.x, position.y, position.z, data.x);
	//gl_Position = MVP * position;
	gl_Position = MVP * t;
}
