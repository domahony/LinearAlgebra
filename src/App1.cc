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
#include "Cube.h"
#include "Sphere.h"
#include "IcoSphere.h"
#include "Material.h"
#include <glm/gtc/matrix_transform.hpp>


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
	Shader vshader(GL_VERTEX_SHADER, vertex);
	program.attach_shader(vshader);

	Shader fshader(GL_FRAGMENT_SHADER, fragment);
	program.attach_shader(fshader);

	program.link();

	glEnable(GL_DEPTH_TEST);

	//objects.push_back(new domahony::opengl::Axis(glm::mat4(1.0f), mvp));
	//objects.push_back(new domahony::opengl::Triangles(glm::mat4(1.0f), mvp));
	glm::mat4 loc1 = glm::translate(glm::mat4(1), glm::vec3(2, 0, -5));
	glm::mat4 loc2 = glm::translate(glm::mat4(1), glm::vec3(-2, 0, -5));
	glm::mat4 loc3 = glm::translate(glm::mat4(1), glm::vec3(0, 4, -15));
	glm::mat4 loc4 = glm::rotate(
			glm::translate(glm::mat4(1), glm::vec3(0, 0, 0)),
			static_cast<float>(M_PI/10), glm::vec3(0,1,1));

	domahony::framework::Material m1(glm::vec3(.6), 1);
	domahony::framework::Material m2(glm::vec3(1), 256);
	domahony::framework::Material m3(glm::vec3(.8), 10);
	domahony::framework::Material m4(glm::vec3(0), 10);

	objects.push_back(new domahony::opengl::IcoSphere(program, loc1, m1, 3));
	objects.push_back(new domahony::opengl::IcoSphere(program, loc2, m2, 3));
	objects.push_back(new domahony::opengl::IcoSphere(program, loc3, m3, 3));
	//objects.push_back(new domahony::opengl::IcoSphere(program, loc4, m4, 3));

	objects.push_back(new domahony::opengl::Cube(program, loc4, m2));

	//objects.push_back(new domahony::opengl::Cube(glm::mat4(1.0f), uniform));

	glViewport(0, 0, width, height);

	return 1;
}

bool App1::
resize(const SDL_ResizeEvent& r)
{
	width = r.w;
	height = r.h;

	surface = SDL_SetVideoMode(width, height, surface->format->BitsPerPixel, surface->flags);
	camera.update_perspective(width, height);
	glViewport(0, 0, width, height);

	return true;
}

bool App1::
key(const SDL_KeyboardEvent& e)
{

	bool ret = false;
	if (e.type == SDL_KEYUP) {
		return ret;
	}

	switch (e.keysym.sym) {
	case SDLK_UP:

		if (e.keysym.mod & KMOD_SHIFT) {
			camera.get_light().up();
		} else {
			camera.up();
		}

		ret = true;
		break;
	case SDLK_DOWN:

		if (e.keysym.mod & KMOD_SHIFT) {
			camera.get_light().down();
		} else {
			camera.down();
		}

		ret = true;
		break;
	case SDLK_LEFT:

		if (e.keysym.mod & KMOD_SHIFT) {
			camera.get_light().left();
		} else {
			camera.left();
		}

		ret = true;
		break;
	case SDLK_RIGHT:
		if (e.keysym.mod & KMOD_SHIFT) {
			camera.get_light().right();
		} else {
			camera.right();
		}
		ret = true;
		break;
	case SDLK_i:
		if (e.keysym.mod & KMOD_SHIFT) {
			camera.get_light().in();
		} else {
			camera.in();
		}
		ret = true;
		break;
	case SDLK_o:

		if (e.keysym.mod & KMOD_SHIFT) {
			camera.get_light().out();
		} else {
			camera.out();
		}
		ret = true;
		break;
	}

	return ret;
}

int App1::
_display(const domahony::framework::Camera& c)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);

	glm::mat4 viewMatrix = c.view();
	glUniformMatrix3fv(uniform["VIEW"], 1, GL_FALSE, &viewMatrix[0][0]);

	glm::vec3 location = c.location();
	glUniform3fv(uniform["EYE"], 1, &location[0]);

	float gloss = 10;
	glUniform1f(uniform["GLOSS"], gloss);

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
