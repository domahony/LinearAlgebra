/*
 * App2.h
 *
 *  Created on: 2013-09-05
 *      Author: domahony
 */

#ifndef APP2_H_
#define APP2_H_

#include "App.h"
#include "Physics.h"
#include "Display.h"
#include "Camera.h"
#include "Light.h"
#include "OpenGL.h"
#include <vector>
#include "AppObject.h"
#include <boost/shared_ptr.hpp>

namespace domahony {
namespace applications {

class App2: public domahony::sdl::App {
public:
	App2(const int& width=640, const int& height=480);
	virtual ~App2();

	int _init();
	int _display();
	int _tick();

protected:
	bool key(const SDL_KeyboardEvent& k);
	bool window(const SDL_WindowEvent& w);
	bool motion(const SDL_MouseMotionEvent& r);
	bool button(const SDL_MouseButtonEvent& b);

private:
	domahony::display::Display display;
	domahony::physics::Physics physics;
	domahony::framework::Camera camera;
	domahony::framework::Light light;
	std::vector<boost::shared_ptr<AppObject> > object;
	AppObject *active;

};

} /* namespace applications */
} /* namespace domahony */
#endif /* APP2_H_ */
