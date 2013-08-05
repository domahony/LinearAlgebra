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

const std::string Program::MVP = "MVP";
const std::string Program::VIEW = "VIEW";
const std::string Program::EYE = "EYE";

const std::string Program::LIGHT_DIR = "LIGHT_DIR";
const std::string Program::LIGHT_COLOR = "LIGHT_COLOR";

const std::string Program::SPECULAR_COLOR = "SPECULAR_COLOR";
const std::string Program::GLOSS = "GLOSS";
const std::string Program::GLOBAL_LIGHT = "GLOBAL_LIGHT";

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

	uniform[MVP] = glGetUniformLocation(program, Program::MVP.c_str());
	uniform[VIEW] = glGetUniformLocation(program, VIEW.c_str());
	uniform[EYE] = glGetUniformLocation(program, EYE.c_str());

	uniform[LIGHT_DIR] = glGetUniformLocation(program, LIGHT_DIR.c_str());
	uniform[LIGHT_COLOR] = glGetUniformLocation(program, LIGHT_COLOR.c_str());

	uniform[SPECULAR_COLOR] = glGetUniformLocation(program, SPECULAR_COLOR.c_str());
	uniform[GLOSS] = glGetUniformLocation(program, GLOSS.c_str());
	uniform[GLOBAL_LIGHT] = glGetUniformLocation(program, GLOBAL_LIGHT.c_str());
}

Program::~Program() {
	// TODO Auto-generated destructor stub
}

} /* namespace opengl */
} /* namespace domahony */
