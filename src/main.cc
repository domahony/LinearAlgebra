#include <SDL.h>
#include "App.h"
#include "Triangles.h"

int
main(int argc, char **argv)
{
	domahony::opengl::Triangles t(640,480);
	domahony::sdl::App& a = t;

	a.start();
}
