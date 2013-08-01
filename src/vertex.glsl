#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 MVP;
uniform mat3 VIEW;
uniform vec3 eye;

uniform int gloss;
uniform vec3 light;
uniform vec3 light_color;

smooth out vec4 color;

void main()
{
	float g = .1;
	vec3 l = normalize(VIEW * vec3(0, 0, 1));
	//vec4 l = normalize(vec4(0, 0, 10, 0));
	vec4 lc = vec4(1,1,1,0);
	
	
	vec3 n = normalize(VIEW * normal);
	vec3 e = normalize(eye);
	
	vec3 h = (e + l) / length(e+l);	
	
	vec3 r = (2 * (max(0, dot(n,l)) * n)) - l;
	
	vec4 mat_color = vec4(1,1,0,0);
	
	gl_Position = MVP * vec4(position, 1);
	color = (lc * mat_color) * pow(max(0, dot(e, r)), g);
	//color = (lc * mat_color) * pow(clamp(dot(n, h), 0, 1), g);
	//color = (lc * mat_color) * pow(max(0, dot(n, h)), g);
	//color = vec4(n, 1);
}
