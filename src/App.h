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

	bool display() {
		_display();
	}

protected:
	virtual bool resize(const SDL_ResizeEvent &);
	virtual bool expose(const SDL_ExposeEvent &);
	virtual bool activate(const SDL_ActiveEvent &);
	virtual bool key(const SDL_KeyboardEvent &);
	virtual bool motion(const SDL_MouseMotionEvent &);
	virtual bool button(const SDL_MouseButtonEvent &);
	virtual bool quit(const SDL_QuitEvent &);

	virtual int _init() = 0;
	virtual int _display() = 0;

	virtual ~App() {}

private:
	int done;
	const int initialized;
};

} /* namespace sdl */
} /* namespace domahony */
#endif /* APP_H_ */
