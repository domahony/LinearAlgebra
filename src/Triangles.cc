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

using domahony::framework::Camera;

Triangles::Triangles(const GLint& mvp):
			Drawable(mvp),
			vbo1(), model(glm::mat4(1.0f))
{
	GLfloat vertexPositions[] = {
	    0.75f, 0.75f, 0.0f, 1.0f,
	    0.75f, -0.75f, 0.0f, 1.0f,
	    -0.75f, -0.75f, 0.0f, 1.0f,
	};

	std::vector<GLfloat> data(vertexPositions, vertexPositions + (sizeof(vertexPositions) / sizeof(GLfloat)));
	vbo1.buffer_data(data);

	GLfloat lines[] = {
	    1.0f, 0.0f, 0.0f, 1.0f,
	    -1.0f, 0.0f, 0.0f, 1.0f,

	    0.0f, 1.0f, 0.0f, 1.0f,
	    0.0f, -1.0f, 0.0f, 1.0f,

	    0.0f, 0.0f, 1.0f, 1.0f,
	    0.0f, 0.0f, -1.0f, 1.0f,

	};

	std::vector<GLfloat> data2(lines, lines + (sizeof(lines) / sizeof(GLfloat)));
}

Triangles::~Triangles() {
	// TODO Auto-generated destructor stub
}

void
Triangles::draw(const Camera& c) const
{
	glm::mat4 MVP = c.projection() * c.view() * model;
	glUniformMatrix4fv(mvp, 1, GL_FALSE, &MVP[0][0]);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	std::cout << "Displayed Called" << std::endl;
}

} /* namespace opengl */
} /* namespace domahony */
