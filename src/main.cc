#include "App3.h"
#include "World.h"
#include "Body3.h"
#include "Body4.h"
#include "Die3.h"
#include "Circle.h"
#include "OpenGLState.h"
#include "Crosshair.h"
#include "GroundPlane.h"
#include "RandomDiceBody.h"

int
main(int argc, char **argv)
{
	domahony::World w;
	domahony::applications::App3 t(640, 480, w);

	boost::shared_ptr<domahony::Die3> die(new domahony::Die3());

	boost::shared_ptr<domahony::RandomDiceBody> r(new domahony::RandomDiceBody(die));
	boost::shared_ptr<domahony::RandomDiceBody> r2(new domahony::RandomDiceBody(die));
	boost::shared_ptr<domahony::RandomDiceBody> r3(new domahony::RandomDiceBody(die));

	/*
	std::vector<boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > > dice;
	boost::shared_ptr<domahony::Die3> d(new domahony::Die3());
	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(d, glm::translate(glm::mat4(1.), glm::vec3(1,15,-.2))));
	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp2(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(d, glm::translate(glm::mat4(5.), glm::vec3(0.5,52,.2))));
	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp3(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(d, glm::translate(glm::mat4(3.), glm::vec3(.8,35,.1))));
	boost::shared_ptr<domahony::Body4<domahony::Die3, domahony::OpenGLState> > bp4(
			new domahony::Body4<domahony::Die3, domahony::OpenGLState>(d, glm::translate(glm::mat4(1.), glm::vec3(-.5,20,0))));
	*/

	/*
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
	*/

	boost::shared_ptr<domahony::Circle> c(new domahony::Circle());

	/*
	boost::shared_ptr<domahony::Body4<domahony::Circle, domahony::Crosshair> > circle(
			new domahony::Body4<domahony::Circle, domahony::Crosshair>(c, glm::translate(glm::mat4(1.), glm::vec3(0,0,0))));
	*/

	boost::shared_ptr<domahony::GroundPlane> gp(new domahony::GroundPlane());

	boost::shared_ptr<domahony::Body4<domahony::GroundPlane, domahony::GroundPlane> > groundplane(
			new domahony::Body4<domahony::GroundPlane, domahony::GroundPlane>(gp, glm::translate(glm::mat4(1.), glm::vec3(0,0,0))));

	w.add_body(r);
	w.add_body(r2);
	w.add_body(r3);
	//w.add_body(bp4);
	w.add_body(groundplane);

	t.start();

	return 1;
}
