/*
 * Triangles.cc
 *
 *  Created on: 2013-06-15
 *      Author: domahony
 */

#include <iostream>
#include <vector>
#include <SDL.h>
#include "Triangles.h"
#include "OpenGL.h"

namespace domahony {
namespace opengl {

static GLuint
init_vao()
{
	GLuint ret;
	glGenVertexArrays(1, &ret);
	glBindVertexArray(ret);

	return ret;
}

Triangles::Triangles(const int&width, const int&height) :
			surface(SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)),
			vao(init_vao()), program(), vbo1(), vbo2(), width(width), height(height) {

}

Triangles::~Triangles() {
	// TODO Auto-generated destructor stub
}

int
Triangles::_init()
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
	vbo2.buffer_data(data2);

	Shader vshader(GL_VERTEX_SHADER, "/home/domahony/Projects/workspace/LinearAlgebra/shaders/vertex.glsl");
	program.attach_shader(vshader);

	Shader fshader(GL_FRAGMENT_SHADER, "/home/domahony/Projects/workspace/LinearAlgebra/shaders/fragment.glsl");
	program.attach_shader(fshader);

	program.link();

	glViewport(0, 0, width, height);

}

int
Triangles::_display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);

	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINES, 0, 6);
	glDisableVertexAttribArray(0);

	glUseProgram(0);

	SDL_GL_SwapBuffers();

	std::cout << "Displayed Called" << std::endl;

}

} /* namespace opengl */
} /* namespace domahony */
