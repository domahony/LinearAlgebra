/*
 * App3.cc
 *
 *  Created on: 2013-09-05
 *      Author: domahony
 */

#include "App3.h"
#include <SDL.h>
#include "OpenGL.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

namespace domahony {
namespace applications {


App3::App3(const int& width, const int& height, domahony::World& world) : App(), display(width, height), world(world)
{
	// TODO Auto-generated constructor stub

}

int App3::
_init()
{

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.f);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDepthRange(0.f, 1.f);
	glFrontFace(GL_CCW);

	return 1;
}

bool App3::
window(const SDL_WindowEvent& w)
{
	bool ret = false;
	switch (w.event) {

	case SDL_WINDOWEVENT_RESIZED :
		display.resize(w.data1, w.data2);
		std::cout << "Window Resize: " << ret << std::endl;
		ret = true;
		break;
	default:
		break;
	}

	return ret;
}

bool App3::
button(const SDL_MouseButtonEvent& b)
{
	return true;
}

bool App3::
motion(const SDL_MouseMotionEvent& m)
{
	return false;
}

bool App3::
wheel(const SDL_MouseWheelEvent& e)
{

	return false;
}

bool App3::
key(const SDL_KeyboardEvent& e)
{
	return false;
}

int App3::
_display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	world.render();

	SDL_GL_SwapWindow(display.get_window());
	return 1;
}

int App3::
_tick()
{
	return world.tick();
}

App3::~App3() {
	// TODO Auto-generated destructor stub
}

} /* namespace applications */
} /* namespace domahony */
