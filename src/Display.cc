/*
 * Display.cc
 *
 *  Created on: 2013-09-05
 *      Author: domahony
 */

#include <SDL.h>
#include "Display.h"

namespace domahony {
namespace display {


static SDL_Window*
init_surface(const int& width, const int&height)
{
	SDL_Window* ret = SDL_CreateWindow("My Game Window",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width, height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	SDL_GLContext glcontext = SDL_GL_CreateContext(ret);

#ifdef _WIN32
	glewInit();
#endif
	return ret;
}

Display::Display(const int& width, const int& height) : window(init_surface(width, height)), width(width), height(height) {
	// TODO Auto-generated constructor stub

}



Display::~Display() {
	// TODO Auto-generated destructor stub
}

void Display::
resize(const int& w, const int& h) {

	width = w;
	height = h;
	SDL_SetWindowSize(window, w, h);

}

} /* namespace display */
} /* namespace domahony */
