/*
 * RandomDiceBody.cc
 *
 *  Created on: Feb 20, 2014
 *      Author: domahony
 */

#include <glm/glm.hpp>
#include "RandomDiceBody.h"
#include <boost/random.hpp>
#include <boost/nondet_random.hpp>
#include <iostream>

namespace domahony {

typedef boost::random_device base_generator_type;

static glm::mat4
get_random_location()
{
		boost::uniform_real<> xdist(0,15);
		boost::uniform_real<> ydist(5,15);
		boost::uniform_real<> zdist(-0.5,0.5);
		boost::random_device dev;
		boost::normal_distribution<float> dist;

		return glm::translate(glm::mat4(1.), glm::vec3(xdist(dev), ydist(dev), zdist(dev)));
}

static glm::vec3
get_random_velocity()
{
		boost::uniform_real<> xdist(-10,10);
		boost::random_device dev;
		boost::normal_distribution<float> dist;

		return glm::vec3(xdist(dev), xdist(dev), xdist(dev));
}

static glm::vec3
get_random_linear_velocity()
{
		boost::uniform_real<> xdist(-20,0);
		boost::uniform_real<> ydist(-3,0);
		boost::uniform_real<> zdist(-.5,.5);
		boost::random_device dev;
		boost::normal_distribution<float> dist;

		return glm::vec3(xdist(dev), ydist(dev), zdist(dev));
}

RandomDiceBody::RandomDiceBody(boost::shared_ptr<domahony::Die3> die) :
		Body4<domahony::Die3, domahony::OpenGLState>(die, get_random_location())
{

}

void RandomDiceBody::
reset()
{
	set_location(get_random_location());
	glm::vec3 va = get_random_velocity();
	glm::vec3 vl = get_random_linear_velocity();
	this->rigid_body->setAngularVelocity(btVector3(va.x, va.y, va.z));
	this->rigid_body->setLinearVelocity(btVector3(vl.x, vl.y, vl.z));
	this->rigid_body->setFriction(1.5);
	activate();
}

void RandomDiceBody::
activate()
{
	this->rigid_body->activate();
}

RandomDiceBody::~RandomDiceBody() {
	// TODO Auto-generated destructor stub
}

} /* namespace domahony */
