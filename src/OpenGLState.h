/*
 * OpenGLState.h
 *
 *  Created on: 2014-01-30
 *      Author: domahony
 */

#ifndef OPENGLSTATE_H_
#define OPENGLSTATE_H_

#include <iostream>
#include "BlenderProgram.h"
#include <vector>
#include "VBO.h"
#include "Light2.h"

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

	void set_light(const glm::vec3& eye, const Light2& light) {
		program.set_light_diffuse(0, light.get_diffuse());
		program.set_light_specular(0, light.get_specular());
		program.set_light_position(0, light.get_position());
		glm::vec3 h = (eye + light.get_position()) / glm::length(eye + light.get_position());
		program.set_light_half_vector(0, h);
	}

	void set_projection_matrix(const glm::mat4& m) {
		//program.set_mvp_matrix(m);
		program.set_projection_matrix(m);
	}

	void set_modelview_matrix(const glm::mat4& m)  {
		program.set_modelview_matrix(m);
	}

	void set_normal_matrix(const glm::mat3& m) {
		program.set_normal_matrix(m);
	}

	void set_data(const std::vector<GLfloat>&);

	void render() const;

private:
	GLuint vao;
	domahony::opengl::BlenderProgram program;
	domahony::opengl::VBO vbo;
	GLenum gl_front_mode;
	GLenum gl_back_mode;

};

} /* namespace domahony */
#endif /* OPENGLSTATE_H_ */
