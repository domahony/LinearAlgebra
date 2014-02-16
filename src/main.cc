#include "App3.h"
#include "World.h"
#include "Body3.h"
#include "Body4.h"
#include "Die3.h"
#include "Circle.h"
#include "OpenGLState.h"
#include "Crosshair.h"

int
main(int argc, char **argv)
{



	domahony::World w;
	domahony::applications::App3 t(640, 480, w);

	std::vector<boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > > dice;

	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(glm::translate(glm::mat4(1.), glm::vec3(0,0,0))));

	float x = -1.5;
	for (int i = 0; i < 2; i++) {
		float y = -1.5;
		for (int j = 0; j < 2; j++) {
			float z = -1.5;
			for (int k = 0; k < 2; k++) {
				boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > copy(
					new domahony::Body4<domahony::Die3, domahony::OpenGLState>(*bp));
				//copy->set_location(glm::translate(glm::mat4(1.), glm::vec3(i * 3,j * 3, k* 3)));
				copy->set_location(glm::translate(glm::mat4(1.), glm::vec3(x, y, z)));
				w.add_body(copy);
				dice.push_back(copy);
				z += 3;
			}
			y += 3;
		}
		x += 3;
	}

	/*
	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp2(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(*bp));
	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp3(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(*bp2));
	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp4(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(*bp3));
	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp5(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(*bp3));
	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp6(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(*bp3));
	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp7(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(*bp3));
	*/

	boost::shared_ptr<domahony::Body4<domahony::Circle, domahony::Crosshair> > circle(
			new domahony::Body4<domahony::Circle, domahony::Crosshair>(glm::translate(glm::mat4(1.), glm::vec3(0,0,0))));
	w.add_body(circle);

	//domahony::Body3Ptr bp(new domahony::Body4<domahony::Die3, domahony::OpenGLState>(glm::translate(glm::mat4(1.), glm::vec3(0,0,0))));
	//domahony::Body3Ptr bp2(new domahony::Body4<domahony::Die3, domahony::OpenGLState>(glm::translate(glm::mat4(1.), glm::vec3(0,0,0))));

	/*
	bp2->set_location(glm::translate(glm::mat4(1.), glm::vec3(0,3,0)));
	bp3->set_location(glm::translate(glm::mat4(1.), glm::vec3(0,-3,0)));
	bp4->set_location(glm::translate(glm::mat4(1.), glm::vec3(0,0,-4)));
	bp5->set_location(glm::translate(glm::mat4(1.), glm::vec3(0,0,4)));
	bp6->set_location(glm::translate(glm::mat4(1.), glm::vec3(3,0,0)));
	bp7->set_location(glm::translate(glm::mat4(1.), glm::vec3(-3,0,0)));


	w.add_body(bp);
	w.add_body(bp2);
	w.add_body(bp3);
	w.add_body(bp4);
	w.add_body(bp5);
	w.add_body(bp6);
	w.add_body(bp7);
	*/

	t.start();

	return 1;
}
