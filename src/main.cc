#include <SDL.h>
#include "App.h"
#include "App1.h"

int
main(int argc, char **argv)
{
	domahony::applications::App1 t(640,480);
	domahony::sdl::App& a = t;

	a.start();
}
