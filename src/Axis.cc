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


static std::vector<GLfloat>
data()
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

	return data2;
}

Axis::
Axis(const glm::mat4& location, const std::map<std::string, GLint>& uniform):
			domahony::applications::Drawable(data(), uniform)
{

}

void Axis::
enableVertexAttributes() const
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void Axis::
doDraw() const
{
	glDrawArrays(GL_LINES, 0, 6);
}

void Axis::
disableVertexAttributes() const
{
	glDisableVertexAttribArray(0);
}

Axis::~Axis() {
	// TODO Auto-generated destructor stub
}

} /* namespace opengl */
} /* namespace domahony */
