/*
 * Crosshair.h
 *
 *  Created on: 2014-02-09
 *      Author: domahony
 */

#ifndef CROSSHAIR_H_
#define CROSSHAIR_H_

#include "Program.h"
#include "VBO.h"
#include <vector>

namespace domahony {

class Crosshair {
public:
	Crosshair();
	virtual ~Crosshair();

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

	void set_projection_matrix(const glm::mat4& m) {
		program.set_projection_matrix(m);
	}

	void set_view_matrix(const glm::mat3& m) {
		program.set_view_matrix(glm::inverse(m));
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
#endif /* CROSSHAIR_H_ */
