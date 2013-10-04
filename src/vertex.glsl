#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 mat_color;

uniform vec3 EYE;
uniform mat4 MVP;
uniform mat3 VIEW;

uniform vec3 LIGHT_DIR;
uniform vec3 LIGHT_COLOR;
uniform float GLOBAL_LIGHT;

uniform vec3 SPECULAR_COLOR;
uniform float GLOSS;

out vec4 color;

void main()
{
	vec3 l = normalize(VIEW * LIGHT_DIR);
	vec4 lc = vec4(LIGHT_COLOR,0);
	
	vec3 n = normalize(VIEW * normal);
	vec3 e = normalize(EYE);
	
	vec3 h = (e + l) / length(e+l);	
	vec3 r = (2 * (max(0, dot(n,l)) * n)) - l;
	
	vec4 mat_s_color = vec4(SPECULAR_COLOR,0);
	vec4 mat_d_color = vec4(mat_color,0);
	//vec4 mat_d_color = vec4(1,1,1,0);
	vec4 gc = lc / GLOBAL_LIGHT;
	
	vec4 s_color = (lc * mat_s_color) * pow(max(0, dot(e, r)), GLOSS);
	//vec4 s_color = (lc * mat_s_color) * pow(max(0, dot(n, h)), GLOSS);
	
	vec4 d_color = (lc * mat_d_color) * max(0, dot(n,l));
	
	vec4 a_color = (gc * mat_d_color);	
	
	color = s_color + d_color + a_color;
	gl_Position = MVP * vec4(position, 1);
}
