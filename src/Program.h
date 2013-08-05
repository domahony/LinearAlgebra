/*
 * Program.h
 *
 *  Created on: 2013-06-08
 *      Author: domahony
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <map>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <string>

namespace domahony {
namespace opengl {

class Program {
public:
	Program();
	void attach_shader(const Shader& shader);
	void link();

	operator GLint () const {
		return program;
	}

	void set_light_direction(const glm::vec3& dir) const {
		glUniform3fv(uniform.at(LIGHT_DIR), 1, glm::value_ptr(dir));
	}

	void set_light_color(const glm::vec3& v) const {
		glUniform3fv(uniform.at(LIGHT_COLOR), 1, glm::value_ptr(v));
	}

	void set_mvp_matrix(const glm::mat4& m) const {
		glUniformMatrix4fv(uniform.at(MVP), 1, GL_FALSE, glm::value_ptr(m));
	}

	void set_view_matrix(const glm::mat3& m) const {
		glUniformMatrix3fv(uniform.at(VIEW), 1, GL_FALSE, glm::value_ptr(m));
	}

	void set_eye_location(const glm::vec3& dir) const {
		glUniform3fv(uniform.at(EYE), 1, glm::value_ptr(dir));
	}

	void set_specular_color(const glm::vec3& v) const {
		glUniform3fv(uniform.at(SPECULAR_COLOR), 1, glm::value_ptr(v));
	}

	void set_gloss(const float& g) const {
		glUniform1f(uniform.at(GLOSS), g);
	}

	void set_global_light(const float& g) const {
		glUniform1f(uniform.at(GLOBAL_LIGHT), g);
	}

	virtual ~Program();

private:
	static const std::string MVP;
	static const std::string VIEW;
	static const std::string EYE;

	static const std::string LIGHT_DIR;
	static const std::string LIGHT_COLOR;

	static const std::string SPECULAR_COLOR;
	static const std::string GLOSS;
	static const std::string GLOBAL_LIGHT;

	const GLint program;
	std::map<std::string, GLint> uniform;

};

} /* namespace opengl */
} /* namespace domahony */
#endif /* PROGRAM_H_ */
