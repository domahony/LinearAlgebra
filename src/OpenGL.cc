/*
 * OpenGL.cc
 *
 *  Created on: 2013-06-06
 *      Author: domahony
 */
#include "OpenGL.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <vector>

namespace domahony {

namespace opengl {

using std::string;
using std::ifstream;

static string get_file_contents(const string& file); 

GLint create_shader(GLenum type, const string& str)
{
	GLint shader = glCreateShader(type);
	const char* shader_src = str.c_str();
	glShaderSource(shader, 1, &shader_src, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {

		GLint tmp;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tmp);

		std::vector<GLchar> strInfoLog(tmp);

		glGetShaderInfoLog(shader, tmp, NULL, &strInfoLog[0]);
		
		const char *strShaderType = NULL;		

		switch (type) {
		case GL_VERTEX_SHADER:
		strShaderType = "vertex";
		break;	

		case GL_GEOMETRY_SHADER:
		strShaderType = "geometry";
		break;	

		case GL_FRAGMENT_SHADER:
		strShaderType = "fragment";
		break;

		}

		std::cerr << "Compile Failure in " << strShaderType << " shader " << str << std::endl;
		std::cerr << &strInfoLog[0];
	}
	return shader;
}

string
get_file_contents(const string& file)
{
	ifstream in(file.c_str(), std::ios::in | std::ios::binary);

	if (in) {

		string ret;
		in.seekg(0, std::ios::end);
		ret.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&ret[0], ret.size());
		in.close();
		return ret;
	}
	
	throw (errno);
}

}

}

