/*
 * Program.cc
 *
 *  Created on: 2013-06-08
 *      Author: domahony
 */

#include <iostream>
#include <vector>
#include "OpenGL.h"
#include "Program.h"
#include "Shader.h"

namespace domahony {
namespace opengl {

Program::Program() : program(glCreateProgram()) {
	// TODO Auto-generated constructor stub

}

void Program::
attach_shader(const Shader& shader)
{
	glAttachShader(program, shader);
}

void Program::
link()
{
	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status == GL_FALSE) {
		GLint len;	
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		std::vector<GLchar> log(len);
		
		glGetProgramInfoLog(program, len, NULL, &log[0]);
		std::cerr << "Linker failure: " << &log[0] << std::endl;
	}
}

Program::~Program() {
	// TODO Auto-generated destructor stub
}

} /* namespace opengl */
} /* namespace domahony */
