/*
 * Program.h
 *
 *  Created on: 2013-06-08
 *      Author: domahony
 */

#ifndef BLENDER_PROGRAM_H_
#define BLENDER_PROGRAM_H_

#include <map>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <string>

namespace domahony {
namespace opengl {

class BlenderProgram {
public:
	BlenderProgram();
	void attach_shader(const Shader& shader);
	void link();

	operator GLint () const {
		return program;
	}

	void set_light_position(const int idx, const glm::vec3& dir) const {

		std::string name;
		switch(idx) {
		case 0:
			name = LIGHT_0_POSITION;
			break;
		case 1:
			name = LIGHT_1_POSITION;
			break;
		case 2:
			name = LIGHT_2_POSITION;
			break;
		default:
			return;
			break;
		}
		set(name, dir);
	}

	void set_light_diffuse(const int idx, const glm::vec3& dir) const {

		std::string name;
		switch(idx) {
		case 0:
			name = LIGHT_0_DIFFUSE;
			break;
		case 1:
			name = LIGHT_1_DIFFUSE;
			break;
		case 2:
			name = LIGHT_2_DIFFUSE;
			break;
		default:
			return;
			break;
		}
		set(name, dir);
	}

	void set_light_half_vector(const int idx, const glm::vec3& dir) const {

		std::string name;
		switch(idx) {
		case 0:
			name = LIGHT_0_HALFVECTOR;
			break;
		case 1:
			name = LIGHT_1_HALFVECTOR;
			break;
		case 2:
			name = LIGHT_2_HALFVECTOR;
			break;
		default:
			return;
			break;
		}
		set(name, dir);
	}

	void set_light_specular(const int idx, const glm::vec3& dir) const {

		std::string name;
		switch(idx) {
		case 0:
			name = LIGHT_0_SPECULAR;
			break;
		case 1:
			name = LIGHT_1_SPECULAR;
			break;
		case 2:
			name = LIGHT_2_SPECULAR;
			break;
		default:
			return;
			break;
		}
		set(name, dir);
	}

	void set(const std::string& name, const glm::vec3& val) const {
			glUniform3fv(uniform.at(name), 1, glm::value_ptr(val));
	}

	void set_modelview_matrix(const glm::mat4& m) const {
		glUniformMatrix4fv(uniform.at(GL_MVM), 1, GL_FALSE, glm::value_ptr(m));
		glm::mat4 inv = glm::inverse(m);
		glUniformMatrix4fv(uniform.at(GL_MVM_I), 1, GL_FALSE, glm::value_ptr(inv));
	}

	void set_projection_matrix(const glm::mat4& m) const {
		glUniformMatrix4fv(uniform.at(GL_PM), 1, GL_FALSE, glm::value_ptr(m));
	}

	void set_normal_matrix(const glm::mat3& m) const {
		glUniformMatrix3fv(uniform.at(GL_NM), 1, GL_FALSE, glm::value_ptr(m));
	}

	virtual ~BlenderProgram();

private:
	static const std::string GL_MVM;
	static const std::string GL_MVM_I;
	static const std::string GL_NM;
	static const std::string GL_PM;

	static const std::string LIGHT_0_POSITION;
	static const std::string LIGHT_0_DIFFUSE;
	static const std::string LIGHT_0_HALFVECTOR;
	static const std::string LIGHT_0_SPECULAR;

	static const std::string LIGHT_1_POSITION;
	static const std::string LIGHT_1_DIFFUSE;
	static const std::string LIGHT_1_HALFVECTOR;
	static const std::string LIGHT_1_SPECULAR;

	static const std::string LIGHT_2_POSITION;
	static const std::string LIGHT_2_DIFFUSE;
	static const std::string LIGHT_2_HALFVECTOR;
	static const std::string LIGHT_2_SPECULAR;
	const GLint program;
	std::map<std::string, GLint> uniform;

};

} /* namespace opengl */
} /* namespace domahony */
#endif /* PROGRAM_H_ */
