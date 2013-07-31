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
Drawable(const std::vector<GLfloat>& data, const GLint& mvp) :
vbo(), mvp(mvp)
{
	vbo.buffer_data(data);
}


void
Drawable::draw(const domahony::framework::Camera& c)
{
	vbo.bind();

	enableVertexAttributes();
	doDraw(c);

	disableVertexAttributes();

	std::cout << "Displayed Called" << std::endl;
}

} /* namespace applications */
} /* namespace domahony */
