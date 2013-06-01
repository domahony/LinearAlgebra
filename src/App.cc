/*
 * App.cpp
 *
 *  Created on: 2013-05-30
 *      Author: domahony
 */

#include <SDL.h>
#include "App.h"

namespace domahony {
namespace sdl {

App::
App() : initialized(SDL_Init(SDL_INIT_EVERYTHING)), done(false)
{

}

void App::
start()
{
	init();
	display();

	SDL_Event event;

	while (!done) {

		SDL_WaitEvent(&event);
		do {

			switch (event.type) {
			case SDL_ACTIVEEVENT:
				activate(event.active);
				break;
			case SDL_KEYUP:
				key(event.key);
				break;
			case SDL_KEYDOWN:
				key(event.key);
				break;
			case SDL_MOUSEMOTION:
				motion(event.motion);
				break;
			case SDL_MOUSEBUTTONUP:
				button(event.button);
				break;
			case SDL_MOUSEBUTTONDOWN:
				button(event.button);
				break;
			case SDL_VIDEORESIZE:
				resize(event.resize);
				break;
			case SDL_VIDEOEXPOSE:
				resize(event.resize);
				break;
			case SDL_QUIT:
				quit(event.quit);
				break;
			}

		} while (SDL_PollEvent(&event));
	}

	SDL_Quit();
}

bool App::
resize(const SDL_ResizeEvent &)
{
	return false;
}

bool App::
expose(const SDL_ExposeEvent &)
{
	return false;
}

bool App::
activate(const SDL_ActiveEvent &)
{
	return false;
}

bool App::
key(const SDL_KeyboardEvent &)
{
	return false;
}

bool App::
motion(const SDL_MouseMotionEvent &)
{
	return false;
}

bool App::
button(const SDL_MouseButtonEvent &)
{
	return false;
}

bool App::
quit(const SDL_QuitEvent &)
{
	return false;
}


} /* namespace sdl */
} /* namespace domahony */
