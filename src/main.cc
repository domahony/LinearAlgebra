#include "App3.h"
#include "World.h"
#include "Body3.h"
#include "Body4.h"
#include "Die3.h"
#include "OpenGLState.h"

int
main(int argc, char **argv)
{

	domahony::World w;
	domahony::applications::App3 t(640, 480, w);

	domahony::Body3Ptr bp(new domahony::Body4<domahony::Die3, domahony::OpenGLState>(glm::translate(glm::mat4(1.), glm::vec3(0,0,0))));

	w.add_body(bp);

	t.start();

	return 1;
}
