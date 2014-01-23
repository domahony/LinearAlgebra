/*
 * App.cpp
 *
 *  Created on: 2013-05-30
 *      Author: domahony
 */

#include <iostream>
#include <SDL.h>
#include <ctime>
#include "App.h"

namespace domahony {
namespace sdl {

App::
App() : initialized(SDL_Init(SDL_INIT_EVERYTHING)), done(false)
{

}

int App::
init()
{
	//SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	return _init();
}

void App::
start()
{
	init();
	display();

	SDL_Event event;

	double control_rate = 1/static_cast<double>(120);
	double tick_rate = 0;

	clock_t last_tick = clock();
	double frame_time = 0;

	while (!done) {

		clock_t cur_tick = clock();

		double delta = static_cast<double>((cur_tick - last_tick)) / CLOCKS_PER_SEC;

		frame_time += delta;
		last_tick = cur_tick;

		if (frame_time < control_rate) {
			continue;
		}

		std::cout.precision(5);

		frame_time -= control_rate;
		//std::cout << "DIFF: " << std::fixed << frame_time << std::endl;
		//std::cout << "Control time: " << std::fixed << control_rate << std::endl;
		bool doDisplay = false;

		while (SDL_PollEvent(&event)) {

			switch (event.type) {
			case SDL_WINDOWEVENT:
				doDisplay = window(event.window);
				break;
			case SDL_KEYUP:
				doDisplay = key(event.key);
				break;
			case SDL_KEYDOWN:
				doDisplay = key(event.key);
				break;
			case SDL_MOUSEMOTION:
				doDisplay = motion(event.motion);
				break;
			case SDL_MOUSEBUTTONUP:
				doDisplay = button(event.button);
				break;
			case SDL_MOUSEBUTTONDOWN:
				doDisplay = button(event.button);
				break;
			case SDL_MOUSEWHEEL:
				doDisplay = wheel(event.wheel);
				break;
			case SDL_QUIT:
				doDisplay = quit(event.quit);
				break;
			}

		}

		if (tick() || doDisplay) {
			_display();
		}

	}

	SDL_Quit();
}

bool App::
window(const SDL_WindowEvent &)
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
wheel(const SDL_MouseWheelEvent &)
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
