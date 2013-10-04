#include <SDL.h>
#include "App.h"
#include "App2.h"

int
main(int argc, char **argv)
{
	domahony::applications::App2 t(640, 480);
	//domahony::sdl::App& a = t;

	t.start();

	return 1;
}
