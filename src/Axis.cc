/*
 * Axis.cc
 *
 *  Created on: 2013-06-15
 *      Author: domahony
 */

#include "Axis.h"
#include <iostream>
#include <vector>
#include <SDL.h>
#include "OpenGL.h"
#include "Camera.h"

namespace domahony {
namespace opengl {

using domahony::framework::Camera;

Axis::Axis(const GLint& mvp):
			Drawable(mvp),
			vbo1(), model(glm::mat4(1.0f))
{

	GLfloat lines[] = {
	    1.0f, 0.0f, 0.0f, 1.0f,
	    -1.0f, 0.0f, 0.0f, 1.0f,

	    0.0f, 1.0f, 0.0f, 1.0f,
	    0.0f, -1.0f, 0.0f, 1.0f,

	    0.0f, 0.0f, 1.0f, 1.0f,
	    0.0f, 0.0f, -1.0f, 1.0f,

	};

	std::vector<GLfloat> data2(lines, lines + (sizeof(lines) / sizeof(GLfloat)));
	vbo1.buffer_data(data2);
}

Axis::~Axis() {
	// TODO Auto-generated destructor stub
}

void
Axis::draw(const Camera& c) const
{
	glm::mat4 MVP = c.projection() * c.view() * model;
	glUniformMatrix4fv(mvp, 1, GL_FALSE, &MVP[0][0]);


	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINES, 0, 6);
	glDisableVertexAttribArray(0);

	std::cout << "Displayed Called" << std::endl;
}

} /* namespace opengl */
} /* namespace domahony */
