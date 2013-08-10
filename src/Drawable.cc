/*
 * Drawable.cc
 *
 *  Created on: 2013-06-19
 *      Author: domahony
 */

#include "Drawable.h"
#include "OpenGL.h"
#include <iostream>
#include <map>

namespace domahony {
namespace applications {

Drawable::
Drawable(const domahony::opengl::Program& program, const std::vector<GLfloat>& data, const glm::mat4& location,
		const domahony::framework::Material& m) :
		program(program), vbo(), material(m)
{
	this->location.push(location);
	vbo.buffer_data(data);
}

void
Drawable::draw(const domahony::framework::Camera& c)
{
	/*
	 * draw something at this location
	 */
	program.set_eye_location(c.location());

	program.set_light_direction(c.get_light().get_direction());
	program.set_light_color(c.get_light().get_color());
	program.set_global_light(c.get_light().get_global());

	/*
	glm::mat4 mvp = c.projection() * c.view() * location;
	program.set_mvp_matrix(mvp);
	*/

	program.set_view_matrix(glm::mat3(c.view()));
	program.set_mvp_matrix(c.projection() * c.view() * location.top());

	/*
	glm::mat3 view = glm::mat3(c.view());
	program.set_view_matrix(view);
	*/

	program.set_specular_color(material.get_specular_color());
	program.set_gloss(material.get_gloss());

	vbo.bind();

	enableVertexAttributes();
	doDraw(c);

	disableVertexAttributes();

	std::cout << "Displayed Called" << std::endl;
}

} /* namespace applications */
} /* namespace domahony */
