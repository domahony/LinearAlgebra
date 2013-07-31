/*
 * App1.h
 *
 *  Created on: 2013-06-18
 *      Author: domahony
 */

#ifndef APP1_H_
#define APP1_H_

#include "App.h"
#include "Camera.h"
#include "Drawable.h"
#include "OpenGL.h"
#include "Program.h"
#include <boost/ptr_container/ptr_vector.hpp>

#ifdef __cplusplus
extern "C" {
#endif
extern char fragment[];
extern char vertex[];
#ifdef __cplusplus
}
#endif

namespace domahony {
namespace applications {

class App1: public domahony::sdl::App {
public:
	App1(const int& width=640, const int& height=480);

	int _init();
	int _display(const domahony::framework::Camera&);

	virtual ~App1();

protected:
	bool key(const SDL_KeyboardEvent& k);

private:
	SDL_Surface *surface;
	GLuint vao;
	domahony::opengl::Program program;
	GLint mvp;
	GLint view;
	GLint eye;
	GLint model;
	boost::ptr_vector<Drawable> objects;
	int width;
	int height;

};

} /* namespace applications */
} /* namespace domahony */
#endif /* APP1_H_ */
