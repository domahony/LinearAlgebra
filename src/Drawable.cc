/*
 * Drawable.cc
 *
 *  Created on: 2013-06-19
 *      Author: domahony
 */

#include "Drawable.h"
#include "OpenGL.h"
#include <iostream>

namespace domahony {
namespace applications {

Drawable::
Drawable(const std::vector<GLfloat>& data, const glm::mat4& location, const GLint& mvp) :
vbo(), location(location), mvp(mvp)
{
	vbo.buffer_data(data);
}


void
Drawable::draw(const domahony::framework::Camera& c)
{
	glm::mat4 MVP = c.projection() * c.view() * location;
	glUniformMatrix4fv(mvp, 1, GL_FALSE, &MVP[0][0]);

	vbo.bind();

	enableVertexAttributes();
	doDraw();

	disableVertexAttributes();

	std::cout << "Displayed Called" << std::endl;
}

} /* namespace applications */
} /* namespace domahony */
