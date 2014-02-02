/*
 * App3.h
 *
 *  Created on: 2013-09-05
 *      Author: domahony
 */

#ifndef APP3_H_
#define APP3_H_

#include "App.h"
#include "Display.h"
#include "World.h"

namespace domahony {
namespace applications {

class App3: public domahony::sdl::App {
public:
	App3(const int& width, const int& height, domahony::World& world);
	virtual ~App3();

	int _init();
	int _display();
	int _tick();

protected:
	bool key(const SDL_KeyboardEvent& k);
	bool window(const SDL_WindowEvent& w);
	bool motion(const SDL_MouseMotionEvent& r);
	bool button(const SDL_MouseButtonEvent& b);
	bool wheel(const SDL_MouseWheelEvent& b);

private:
	domahony::display::Display display;
	domahony::World world;

};

} /* namespace applications */
} /* namespace domahony */
#endif /* APP2_H_ */
