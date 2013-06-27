/*
 * Cube.cc
 *
 *  Created on: 2013-06-24
 *      Author: domahony
 */

#include "Cube.h"
#include <iostream>
#include <vector>
#include <SDL.h>
#include "OpenGL.h"

namespace domahony {
namespace opengl {

static std::vector<GLfloat> data() {
	GLfloat vertexPositions[] = {
			0.75f, 0.75f, 0.0f, 1.0f, 0.75f, -0.75f, 0.0f,
			1.0f, -0.75f, -0.75f, 0.0f, 1.0f,
	};

	std::vector<GLfloat> data(vertexPositions,
			vertexPositions + (sizeof(vertexPositions) / sizeof(GLfloat)));

	return data;
}

Cube::Cube(const glm::mat4& location, const GLint& mvp) :
		domahony::applications::Drawable(data(), location, mvp) {

}

void Cube::enableVertexAttributes() const {
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void Cube::doDraw() const {
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Cube::disableVertexAttributes() const {
	glDisableVertexAttribArray(0);
}

Cube::~Cube() {
	// TODO Auto-generated destructor stub
}

} /* namespace opengl */
} /* namespace domahony */
