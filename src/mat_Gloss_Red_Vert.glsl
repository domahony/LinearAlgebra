#version 330

struct Light {
	vec3 position;	
	vec3 diffuse;
	vec3 halfVector;	
	vec3 specular;
};

layout(location = 0) in vec3 GL_VERTEX; //gl_Vertex
layout(location = 1) in vec3 GL_NORMAL; //gl_Normal
layout(location = 2) in vec3 mat_color;

uniform mat4 GL_MVM; //gl_ModelViewMatrix
uniform mat4 GL_MVM_I; //gl_ModelViewMatrix
uniform mat3 GL_NM; //gl_NormalMatrix
uniform mat4 GL_PM; //gl_ProjectionMatrix
uniform Light LIGHT[3];

out vec4 position; 
out vec3 varnormal;
out vec3 varposition;
out vec3 color;

void main()
{
	vec4 co = GL_MVM * vec4(GL_VERTEX, 1);

	varposition = co.xyz;
	varnormal = normalize(GL_NM * GL_NORMAL);
	gl_Position = GL_PM * co;
	color = mat_color;

/*
#ifdef GPU_NVIDIA
	// Setting gl_ClipVertex is necessary to get glClipPlane working on NVIDIA
	// graphic cards, while on ATI it can cause a software fallback.
	gl_ClipVertex = gl_ModelViewMatrix * gl_Vertex; 
#endif 
*/

}

