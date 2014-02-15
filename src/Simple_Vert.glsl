#version 330

layout(location = 0) in vec3 position;

uniform mat4 PROJECTION;

out vec4 color;

void main()
{
	gl_Position = PROJECTION * vec4(position, 1);
}

