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

	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(glm::translate(glm::mat4(1.), glm::vec3(0,0,0))));
	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp2(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(*bp));
	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp3(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(*bp2));
	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp4(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(*bp3));

	//domahony::Body3Ptr bp(new domahony::Body4<domahony::Die3, domahony::OpenGLState>(glm::translate(glm::mat4(1.), glm::vec3(0,0,0))));
	//domahony::Body3Ptr bp2(new domahony::Body4<domahony::Die3, domahony::OpenGLState>(glm::translate(glm::mat4(1.), glm::vec3(0,0,0))));

	bp2->set_location(glm::translate(glm::mat4(1.), glm::vec3(0,4,0)));
	bp3->set_location(glm::translate(glm::mat4(1.), glm::vec3(0,-4,0)));
	bp4->set_location(glm::translate(glm::mat4(1.), glm::vec3(0,0,-9)));


	w.add_body(bp);
	w.add_body(bp2);
	w.add_body(bp3);
	w.add_body(bp4);

	t.start();

	return 1;
}
