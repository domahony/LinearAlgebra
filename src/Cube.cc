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
			/* front */
			0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,
			0.5f, -0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f,

			/* bottom */
			0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			/* back */
			0.5f, 0.5f, -0.5f,
			-0.5f, 0.5f, -0.5f,

			/* top */
			0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,

			/* right */
			0.5f, 0.5f, 0.5f,
			0.5f, 0.5f, -0.5f,
			0.5f, -0.5f, 0.5f,
			0.5f, -0.5f, -0.5f,

			/* left */
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, 0.5f,
			-0.5f, 0.5f, -0.5f,
			-0.5f, 0.5f, 0.5f,
	};

	std::vector<GLfloat> data(vertexPositions,
			vertexPositions + (sizeof(vertexPositions) / sizeof(GLfloat)));

	return data;
}

Cube::Cube(const glm::mat4& location, const GLint& mvp) :
		domahony::applications::Drawable(data(), location, mvp), idx(GL_ELEMENT_ARRAY_BUFFER)
{

	std::vector<GLushort> idx_data;

	/* front */
	idx_data.push_back(0);
	idx_data.push_back(1);
	idx_data.push_back(2);
	idx_data.push_back(3);

	/* bottom */
	idx_data.push_back(4);
	idx_data.push_back(5);

	/* back */
	idx_data.push_back(6);
	idx_data.push_back(7);

	/* top */
	idx_data.push_back(8);
	idx_data.push_back(9);

	/* right */
	idx_data.push_back(10);
	idx_data.push_back(10);
	idx_data.push_back(11);
	idx_data.push_back(12);
	idx_data.push_back(13);

	/* left */
	idx_data.push_back(14);
	idx_data.push_back(14);
	idx_data.push_back(15);
	idx_data.push_back(16);
	idx_data.push_back(17);

	idx.buffer_data(idx_data);
}

void Cube::enableVertexAttributes() const {
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void Cube::doDraw() const {
	idx.bind();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode( GL_FRONT, GL_FILL);
	glPolygonMode( GL_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLE_STRIP, 20, GL_UNSIGNED_SHORT, 0);
	//glDrawArrays(GL_LINE_STRIP, 0, 24);
}

void Cube::disableVertexAttributes() const {
	glDisableVertexAttribArray(0);
}

Cube::~Cube() {
	// TODO Auto-generated destructor stub
}

} /* namespace opengl */
} /* namespace domahony */
