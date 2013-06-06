#include <SDL.h>
#include "App.h"
#include "Test.h"

int
main(int argc, char **argv)
{
	domahony::test::Test t;
	domahony::sdl::App &app = t;
	app.start();

}
