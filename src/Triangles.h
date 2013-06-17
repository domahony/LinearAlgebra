/*
 * Triangles.h
 *
 *  Created on: 2013-06-15
 *      Author: domahony
 */

#ifndef TRIANGLES_H_
#define TRIANGLES_H_

#include "App.h"
#include "Program.h"
#include "VBO.h"
#include <glm/glm.hpp>

namespace domahony {
namespace opengl {

class Triangles: public domahony::sdl::App {
public:
	Triangles(const int&width=640, const int&height=480);

	virtual ~Triangles();
protected:
	int _init();
	int _display();

private:
	SDL_Surface *surface;
	GLuint vao;
	Program program;
	VBO vbo1;
	VBO vbo2;
	int width;
	int height;

	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;

	GLuint mvp;
};

} /* namespace opengl */
} /* namespace domahony */
#endif /* TRIANGLES_H_ */
