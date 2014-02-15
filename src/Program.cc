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
const std::string Program::PROJECTION = "PROJECTION";
const std::string Program::N_MATRIX = "N_MATRIX";
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

	glUseProgram(program);

	GLint blah;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &blah);

	std::cerr << "Active Uniforms: '" << blah << "'" << std::endl;

	std::cerr << "'" << Program::MVP.c_str() << "'" << std::endl;
	std::cerr << "'" << Program::VIEW.c_str() << "'" << std::endl;
	std::cerr << "'" << Program::EYE.c_str() << "'" << std::endl;
	std::cerr << "'" << Program::LIGHT_DIR.c_str() << "'" << std::endl;
	std::cerr << "'" << Program::LIGHT_COLOR.c_str() << "'" << std::endl;
	std::cerr << "'" << Program::SPECULAR_COLOR.c_str() << "'" << std::endl;
	std::cerr << "'" << Program::GLOSS.c_str() << "'" << std::endl;
	std::cerr << "'" << Program::GLOBAL_LIGHT.c_str() << "'" << std::endl;

	uniform[MVP] = glGetUniformLocation(program, Program::MVP.c_str());
	uniform[VIEW] = glGetUniformLocation(program, Program::VIEW.c_str());
	uniform[EYE] = glGetUniformLocation(program, Program::EYE.c_str());
	uniform[N_MATRIX] = glGetUniformLocation(program, Program::N_MATRIX.c_str());

	uniform[LIGHT_DIR] = glGetUniformLocation(program, Program::LIGHT_DIR.c_str());
	uniform[LIGHT_COLOR] = glGetUniformLocation(program, Program::LIGHT_COLOR.c_str());

	uniform[SPECULAR_COLOR] = glGetUniformLocation(program, Program::SPECULAR_COLOR.c_str());
	uniform[GLOSS] = glGetUniformLocation(program, Program::GLOSS.c_str());
	uniform[GLOBAL_LIGHT] = glGetUniformLocation(program, Program::GLOBAL_LIGHT.c_str());
	uniform[PROJECTION] = glGetUniformLocation(program, Program::PROJECTION.c_str());
}

Program::~Program() {
	// TODO Auto-generated destructor stub
}

} /* namespace opengl */
} /* namespace domahony */
