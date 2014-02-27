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

	boost::shared_ptr<domahony::Circle> c(new domahony::Circle());

	boost::shared_ptr<domahony::Body4<domahony::Circle, domahony::Crosshair> > circle(
			new domahony::Body4<domahony::Circle, domahony::Crosshair>(c, glm::translate(glm::mat4(1.), glm::vec3(0,0,0))));

	boost::shared_ptr<domahony::GroundPlane> gp(new domahony::GroundPlane());
	boost::shared_ptr<domahony::GroundPlane> wall(new domahony::GroundPlane(glm::vec3(1,0,0), -2));

	boost::shared_ptr<domahony::Body4<domahony::GroundPlane, domahony::GroundPlane> > groundplane(
			new domahony::Body4<domahony::GroundPlane, domahony::GroundPlane>(gp, glm::translate(glm::mat4(1.), glm::vec3(0,0,0))));
	boost::shared_ptr<domahony::Body4<domahony::GroundPlane, domahony::GroundPlane> > wall_body(
			new domahony::Body4<domahony::GroundPlane, domahony::GroundPlane>(wall, glm::translate(glm::mat4(1.), glm::vec3(0,0,0))));

	w.add_body(r);
	w.add_body(r2);
	w.add_body(r3);
	//w.add_body(bp4);
	w.add_body(groundplane);
	w.add_body(wall_body);

	t.start();

	return 1;
}
