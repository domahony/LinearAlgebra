/*
 * AppObject.h
 *
 *  Created on: 2013-09-07
 *      Author: domahony
 */

#ifndef APPOBJECT_H_
#define APPOBJECT_H_

#include "OpenGL.h"
#include "Program.h"
#include "Material.h"
#include "VBO.h"
#include "Light.h"
#include "Camera.h"
#include "Body.h"
#include <vector>

namespace domahony {
namespace applications {

using	domahony::opengl::Program;
using	domahony::opengl::VBO;
using	domahony::framework::Material;
using	domahony::physics::Body;

static GLuint
init_vao()
{
	GLuint ret;
	glGenVertexArrays(1, &ret);

	return ret;
}

class AppObject {

public:
	AppObject(const glm::mat4& location, Program& program, const std::vector<GLfloat>& data, Material& material) :
		program(program),
		vbo(),
		material(material),
		body(this, location, 1., 1.),
		vao(init_vao())
	{
		glBindVertexArray(vao);
		vbo.buffer_data(data);

		vbo.bind();

		glVertexAttribPointer(+ 0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), 0);
		glVertexAttribPointer(+ 1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
		glVertexAttribPointer(+ 2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), reinterpret_cast<void*>(6 * sizeof(GLfloat)));

		vbo.unbind();
		glBindVertexArray(0);
	}
	virtual ~AppObject();

	void draw(const domahony::framework::Camera& c, const domahony::framework::Light& l) {

		glUseProgram(program);

		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		program.set_eye_location(c.location());

		program.set_light_direction(l.get_direction());
		program.set_light_color(l.get_color());
		program.set_global_light(l.get_global());

		program.set_mvp_matrix(c.projection() * c.view() * body.get_location());
		program.set_view_matrix(glm::mat3(c.view()));

		program.set_specular_color(material.get_specular_color());
		program.set_gloss(material.get_gloss());

		/*
		 * need to know location of
		 * location = location * local_location
		 *	draw(location)
		 */
		glPolygonMode( GL_FRONT, GL_FILL);
		glPolygonMode( GL_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, vbo.size()/9);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);
	}

	operator domahony::physics::Body& () {
		return body;
	}

	glm::vec3 get_origin() const {

		return body.get_origin();

	}

	void translate(glm::vec4 delta) {

		glm::mat4 l = body.get_location();
		glm::mat4 t = glm::translate(glm::mat4(1.), glm::vec3(delta));


		body.set_location(t*l);
	}

	glm::mat4 get_location() const {

		return body.get_location();

	}

	void set_location(glm::vec3 location) {
		body.set_location(location);
	}

	void set_location(const glm::mat4& location) {
		body.set_location(location);
	}

private:
	domahony::opengl::Program program;
	domahony::opengl::VBO vbo;
	domahony::framework::Material material;
	domahony::physics::Body body;
	int vao;

};

} /* namespace applications */
} /* namespace domahony */
#endif /* APPOBJECT_H_ */
