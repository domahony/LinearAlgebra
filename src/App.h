/*
 * App.h
 *
 *  Created on: 2013-05-30
 *      Author: domahony
 */

#ifndef APP_H_
#define APP_H_

#include <SDL.h>

namespace domahony {
namespace sdl {

class App {
public:
	App();

	void start();
	int init();

	int display() {
		return _display();
	}

	int tick() {
		return _tick();
	}

protected:
	virtual bool window(const SDL_WindowEvent &);
	virtual bool key(const SDL_KeyboardEvent &);
	virtual bool motion(const SDL_MouseMotionEvent &);
	virtual bool button(const SDL_MouseButtonEvent &);
	virtual bool wheel(const SDL_MouseWheelEvent &);
	virtual bool quit(const SDL_QuitEvent &);

	virtual bool joystick(const SDL_JoyAxisEvent &);
	virtual bool joystick(const SDL_JoyBallEvent &);
	virtual bool joystick(const SDL_JoyButtonEvent &);
	virtual bool joystick(const SDL_JoyDeviceEvent &);
	virtual bool joystick(const SDL_JoyHatEvent &);

	virtual int _init() = 0;
	virtual int _display() = 0;
	virtual int _tick() = 0;

	virtual ~App() {}

private:
	int done;
	const int initialized;
};

} /* namespace sdl */
} /* namespace domahony */
#endif /* APP_H_ */
