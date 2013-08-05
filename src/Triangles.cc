/*
 * Triangles.cc
 *
 *  Created on: 2013-06-15
 *      Author: domahony
 */

#include "Triangles.h"
#include <iostream>
#include <vector>
#include <SDL.h>
#include "OpenGL.h"
#include "Camera.h"

namespace domahony {
namespace opengl {

static std::vector<GLfloat>
data()
{
	GLfloat vertexPositions[] = {
	    0.75f, 0.75f, 0.0f, 1.0f,
	    0.75f, -0.75f, 0.0f, 1.0f,
	    -0.75f, -0.75f, 0.0f, 1.0f,
	};

	std::vector<GLfloat> data(vertexPositions, vertexPositions + (sizeof(vertexPositions) / sizeof(GLfloat)));

	return data;
}

Triangles::
Triangles(const glm::mat4& location, const std::map<std::string, GLint>& uniform):
			domahony::applications::Drawable(data(), uniform)
{

}

void Triangles::
enableVertexAttributes() const
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void Triangles::
doDraw() const
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangles::
disableVertexAttributes() const
{
	glDisableVertexAttribArray(0);
}

Triangles::~Triangles() {
	// TODO Auto-generated destructor stub
}

} /* namespace opengl */
} /* namespace domahony */
