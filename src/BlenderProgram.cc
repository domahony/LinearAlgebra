/*
 * Program.cc
 *
 *  Created on: 2013-06-08
 *      Author: domahony
 */

#include <iostream>
#include <vector>
#include "OpenGL.h"
#include "BlenderProgram.h"
#include "Shader.h"

namespace domahony {
namespace opengl {

	const std::string BlenderProgram::GL_MVM = "GL_MVM";
	const std::string BlenderProgram::GL_MVM_I = "GL_MVM_I";
	const std::string BlenderProgram::GL_NM = "GL_NM";
	const std::string BlenderProgram::GL_PM = "GL_PM";

	const std::string BlenderProgram::LIGHT_0_POSITION = "LIGHT[0].position";
	const std::string BlenderProgram::LIGHT_0_DIFFUSE = "LIGHT[0].diffuse";
	const std::string BlenderProgram::LIGHT_0_HALFVECTOR = "LIGHT[0].halfvector";
	const std::string BlenderProgram::LIGHT_0_SPECULAR = "LIGHT[0].specular";

	const std::string BlenderProgram::LIGHT_1_POSITION = "LIGHT[1].position";
	const std::string BlenderProgram::LIGHT_1_DIFFUSE = "LIGHT[1].diffuse";
	const std::string BlenderProgram::LIGHT_1_HALFVECTOR = "LIGHT[1].halfvector";
	const std::string BlenderProgram::LIGHT_1_SPECULAR = "LIGHT[1].specular";

	const std::string BlenderProgram::LIGHT_2_POSITION = "LIGHT[2].position";
	const std::string BlenderProgram::LIGHT_2_DIFFUSE = "LIGHT[2].diffuse";
	const std::string BlenderProgram::LIGHT_2_HALFVECTOR = "LIGHT[2].halfvector";
	const std::string BlenderProgram::LIGHT_2_SPECULAR = "LIGHT[2].specular";

BlenderProgram::BlenderProgram() : program(glCreateProgram()) {
	// TODO Auto-generated constructor stub

}

void BlenderProgram::
attach_shader(const Shader& shader)
{
	glAttachShader(program, shader);
}

void BlenderProgram::
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

	uniform[GL_MVM] = glGetUniformLocation(program, BlenderProgram::GL_MVM.c_str());
	uniform[GL_MVM_I] = glGetUniformLocation(program, BlenderProgram::GL_MVM_I.c_str());
	uniform[GL_NM] = glGetUniformLocation(program, BlenderProgram::GL_NM.c_str());
	uniform[GL_PM] = glGetUniformLocation(program, BlenderProgram::GL_PM.c_str());

	uniform[LIGHT_0_POSITION] = glGetUniformLocation(program, BlenderProgram::LIGHT_0_POSITION.c_str());
	uniform[LIGHT_0_DIFFUSE] = glGetUniformLocation(program, BlenderProgram::LIGHT_0_DIFFUSE.c_str());
	uniform[LIGHT_0_HALFVECTOR] = glGetUniformLocation(program, BlenderProgram::LIGHT_0_HALFVECTOR.c_str());
	uniform[LIGHT_0_SPECULAR] = glGetUniformLocation(program, BlenderProgram::LIGHT_0_SPECULAR.c_str());

	uniform[LIGHT_1_POSITION] = glGetUniformLocation(program, BlenderProgram::LIGHT_1_POSITION.c_str());
	uniform[LIGHT_1_DIFFUSE] = glGetUniformLocation(program, BlenderProgram::LIGHT_1_DIFFUSE.c_str());
	uniform[LIGHT_1_HALFVECTOR] = glGetUniformLocation(program, BlenderProgram::LIGHT_1_HALFVECTOR.c_str());
	uniform[LIGHT_1_SPECULAR] = glGetUniformLocation(program, BlenderProgram::LIGHT_1_SPECULAR.c_str());

	uniform[LIGHT_2_POSITION] = glGetUniformLocation(program, BlenderProgram::LIGHT_2_POSITION.c_str());
	uniform[LIGHT_2_DIFFUSE] = glGetUniformLocation(program, BlenderProgram::LIGHT_2_DIFFUSE.c_str());
	uniform[LIGHT_2_HALFVECTOR] = glGetUniformLocation(program, BlenderProgram::LIGHT_2_HALFVECTOR.c_str());
	uniform[LIGHT_2_SPECULAR] = glGetUniformLocation(program, BlenderProgram::LIGHT_2_SPECULAR.c_str());
}

BlenderProgram::~BlenderProgram() {
	// TODO Auto-generated destructor stub
}

} /* namespace opengl */
} /* namespace domahony */
