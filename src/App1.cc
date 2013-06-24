/*
 * App1.cc
 *
 *  Created on: 2013-06-18
 *      Author: domahony
 */

#include <SDL.h>
#include "App1.h"
#include "OpenGL.h"
#include "Triangles.h"
#include "Axis.h"



namespace domahony {
namespace applications {

using domahony::opengl::Shader;

static SDL_Surface*
init_surface(const int& width, const int&height)
{
	SDL_Surface* ret = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);
#ifdef _WIN32
	glewInit();
#endif
	return ret;
}

static GLuint
init_vao()
{
	GLuint ret;
	glGenVertexArrays(1, &ret);
	glBindVertexArray(ret);

	return ret;
}

App1::
App1(const int& width, const int& height) :
surface(init_surface(width, height)),
vao(init_vao()),
objects(),
width(width),
height(height)
{
	// TODO Auto-generated constructor stub

}

int App1::
_init()
{


	for (int i = 0; fragment[i]; i++) {
		std::cout << fragment[i];
	}

	Shader vshader(GL_VERTEX_SHADER, vertex);
	program.attach_shader(vshader);

	Shader fshader(GL_FRAGMENT_SHADER, fragment);
	program.attach_shader(fshader);

	program.link();

	mvp = glGetUniformLocation(program, "MVP");

	objects.push_back(new domahony::opengl::Axis(mvp));
	objects.push_back(new domahony::opengl::Triangles(mvp));

	glViewport(0, 0, width, height);

	return 1;
}

int App1::
_display(const domahony::framework::Camera& c)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);

	for (boost::ptr_vector<Drawable>::iterator it = objects.begin(); it != objects.end(); ++it) {
		it->draw(c);
	}

	glUseProgram(0);

	SDL_GL_SwapBuffers();

	return 1;
}

App1::~App1() {
	// TODO Auto-generated destructor stub
}

} /* namespace applications */
} /* namespace domahony */
