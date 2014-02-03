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

	SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	SDL_Joystick *joy;

	// Initialize the joystick subsystem
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	// Check for joystick
	if (SDL_NumJoysticks() > 0) {
	    // Open joystick
	    joy = SDL_JoystickOpen(0);

	    if (joy) {
	        printf("Opened Joystick 0\n");
	        printf("Name: %s\n", SDL_JoystickNameForIndex(0));
	        printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
	        printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
	        printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
	    } else {
	        printf("Couldn't open Joystick 0\n");
	    }

	    // Close if opened
	    //if (SDL_JoystickGetAttached(joy)) {
	    //   SDL_JoystickClose(joy);
	    //}
	}

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
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				doDisplay = joystick(event.jbutton);
				break;
			case SDL_JOYAXISMOTION:
				doDisplay = joystick(event.jaxis);
				break;
			case SDL_JOYHATMOTION:
				doDisplay = joystick(event.jhat);
				break;
			case SDL_QUIT:
				doDisplay = quit(event.quit);
				break;
			}

			if (doDisplay) {
				std::cout << "Do Display: " << doDisplay << std::endl;
			}

			if (tick() || doDisplay) {
				_display();
			}

		}
	}

	SDL_Quit();
}

bool App::
joystick(const SDL_JoyAxisEvent& e)
{
	std::cout << "Axis Value: " << e.value << std::endl;

	return true;
}

bool App::
joystick(const SDL_JoyBallEvent& e)
{
	std::cout << e.ball << std::endl;
	return true;

}

bool App::
joystick(const SDL_JoyButtonEvent& e)
{

	switch (e.state) {
	case SDL_PRESSED:
		std::cout << "Pressed Button Event: " << std::dec << static_cast<int>(e.button) << std::endl;
		break;
	case SDL_RELEASED:
		std::cout << "Released Button Event: " << std::dec << static_cast<int>(e.button) << std::endl;
		break;
	}

	return false;

}

bool App::
joystick(const SDL_JoyDeviceEvent& e)
{
	std::cout << e.type << std::endl;
	return true;

}

bool App::
joystick(const SDL_JoyHatEvent& e)
{
	//std::cout << e.hat << std::endl;
	if (e.value & SDL_HAT_LEFT) {
		std::cout << "Hat Left" << std::endl;
	}
	if (e.value & SDL_HAT_RIGHT) {
		std::cout << "Hat Right" << std::endl;
	}
	if (e.value & SDL_HAT_UP) {
		std::cout << "Hat Up" << std::endl;
	}
	if (e.value & SDL_HAT_DOWN) {
		std::cout << "Hat Down" << std::endl;
	}
	if (e.value == SDL_HAT_CENTERED) {
		std::cout << "Hat Center" << std::endl;
	}

	return true;

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
