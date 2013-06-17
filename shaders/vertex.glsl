#version 330

layout(location = 0) in vec4 position;
uniform mat4 MVP;

void main()
{
	//vec4 v = vec4(position, 1);
	gl_Position = MVP * position;
}
