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
App() : initialized(SDL_Init(SDL_INIT_EVERYTHING)), done(false),
camera(domahony::framework::Light(glm::vec3(0,1,0), glm::vec3(1,1,1), 4))
{

}

int App::
init()
{
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	return _init();
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

			bool ret = false;

			switch (event.type) {
			case SDL_ACTIVEEVENT:
				ret = activate(event.active);
				break;
			case SDL_KEYUP:
				ret = key(event.key);
				break;
			case SDL_KEYDOWN:
				ret = key(event.key);
				break;
			case SDL_MOUSEMOTION:
				ret = motion(event.motion);
				break;
			case SDL_MOUSEBUTTONUP:
				ret = button(event.button);
				break;
			case SDL_MOUSEBUTTONDOWN:
				ret = button(event.button);
				break;
			case SDL_VIDEORESIZE:
				ret = resize(event.resize);
				break;
			case SDL_VIDEOEXPOSE:
				ret = resize(event.resize);
				break;
			case SDL_QUIT:
				ret = quit(event.quit);
				break;
			}

			if (ret) {
				display();
			}

		} while (SDL_PollEvent(&event));
	}

	SDL_Quit();
}

bool App::
resize(const SDL_ResizeEvent &)
{
	return display();
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
	done = true;
	return true;
}


} /* namespace sdl */
} /* namespace domahony */
