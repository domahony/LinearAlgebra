/*
 * OpenGLState.h
 *
 *  Created on: 2014-01-30
 *      Author: domahony
 */

#ifndef OPENGLSTATE_H_
#define OPENGLSTATE_H_

#include <iostream>
#include "Program.h"
#include <vector>
#include "VBO.h"

namespace domahony {

class OpenGLState {
public:
	OpenGLState();
	virtual ~OpenGLState();

	void enable() const {
		glUseProgram(program);
	}

	void disable() const {
		glUseProgram(0);
	}

	void set_eye_location(const glm::vec3& v) {
		program.set_eye_location(v);
	}

	void set_global_light(const float& g) {
		program.set_global_light(g);
	}

	void set_mvp_matrix(const glm::mat4& m) {
		program.set_mvp_matrix(m);
	}

	void set_normal_matrix(const glm::mat3& m) {
		program.set_normal_matrix(m);
	}

	void set_view_matrix(const glm::mat3& m) {
		program.set_view_matrix(m);
	}

	void set_light_direction(const glm::vec3& d) {
		program.set_light_direction(d);
	}

	void set_light_color(const glm::vec3& c) {
		program.set_light_color(c);
	}

	void set_specular_color(const glm::vec3& c) {
		program.set_specular_color(c);
	}

	void set_gloss(const float& g) {
		program.set_gloss(g);
	}

	void set_data(const std::vector<GLfloat>&);

	void render() const;

private:
	GLuint vao;
	domahony::opengl::Program program;
	domahony::opengl::VBO vbo;
	GLenum gl_front_mode;
	GLenum gl_back_mode;

};

} /* namespace domahony */
#endif /* OPENGLSTATE_H_ */
