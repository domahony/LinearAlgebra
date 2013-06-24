/*
 * Test.cc
 *
 *  Created on: 2013-06-04
 *      Author: domahony
 */

#include <iostream>
#include "Test.h"
#include "OpenGL.h"
#include "Shader.h"
#include "Program.h"

namespace domahony {
namespace test {

Test::Test(const int& width, const int& height) : domahony::sdl::App(), width(width), height(height) {
	// TODO Auto-generated constructor stub

}

Test::~Test() {
	// TODO Auto-generated destructor stub
}

int Test::_init() {
	SDL_SetVideoMode(width, height, 32, SDL_OPENGL);

	domahony::opengl::Program p;
	domahony::opengl::Shader vshader(GL_VERTEX_SHADER, "shaders/vertex.glsl");
	p.attach_shader(vshader);

	domahony::opengl::Shader fshader(GL_FRAGMENT_SHADER, "shaders/fragment.glsl");
	p.attach_shader(fshader);

	p.link();

	glUseProgram(p);

	GLuint buf;
	glGenBuffers(1, &buf);
	glBindBuffer(GL_ARRAY_BUFFER, buf);

	GLbyte data[] = {
			-10, 0, 0,
			10, 0, 0,

			0, -10, 0,
			0, 10, 0,

			0, 0, -10,
			0, 0, 10,
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buf);
	
	glVertexAttribPointer(0, 3, GL_BYTE, GL_FALSE, 0, 0);	

	return 1;
}

int Test::_display() {
	std::cout << "Display" << std::endl;
	glDrawArrays(GL_LINES, 0, 6);
	SDL_GL_SwapBuffers();

	return 1;
}

} /* namespace test */
} /* namespace domahony */
