/*
 * App.h
 *
 *  Created on: 2013-05-30
 *      Author: domahony
 */

#ifndef APP_H_
#define APP_H_

#include <SDL.h>
#include <Camera.h>

namespace domahony {
namespace sdl {

class App {
public:
	App();

	void start();
	int init();

	bool display() {
		return _display(camera);
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
	virtual int _display(const domahony::framework::Camera&) = 0;

	virtual ~App() {}

private:
	domahony::framework::Camera camera;
	int done;
	const int initialized;
};

} /* namespace sdl */
} /* namespace domahony */
#endif /* APP_H_ */
