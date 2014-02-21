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
		boost::uniform_real<> xdist(-1,1);
		boost::uniform_real<> ydist(5,30);
		boost::uniform_real<> zdist(-0.5,0.5);
		boost::random_device dev;
		boost::normal_distribution<float> dist;

		return glm::translate(glm::mat4(1.), glm::vec3(xdist(dev), ydist(dev), zdist(dev)));
}

RandomDiceBody::RandomDiceBody(boost::shared_ptr<domahony::Die3> die) :
		Body4<domahony::Die3, domahony::OpenGLState>(die, get_random_location())
{

}

void RandomDiceBody::
reset()
{
	set_location(get_random_location());
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
