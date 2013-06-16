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

};

} /* namespace opengl */
} /* namespace domahony */
#endif /* TRIANGLES_H_ */
