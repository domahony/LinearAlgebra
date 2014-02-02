/*
 * WorldImpl.cc
 *
 *  Created on: 2014-01-25
 *      Author: domahony
 */

#include "Body3.h"
#include "WorldImpl.h"
#include <iostream>

namespace domahony {

using std::cout;
using std::endl;

WorldImpl::WorldImpl() : bodies(), camera(), light(glm::normalize(glm::vec3(-1,-1,0)), glm::vec3(1,1,1), 0.1) {
	// TODO Auto-generated constructor stub

}

WorldImpl::~WorldImpl() {
	// TODO Auto-generated destructor stub
}

void WorldImpl::
render()
{
	cout << "Render" << endl;
	for (std::vector<Body3Ptr>::const_iterator iter = bodies.begin(); iter != bodies.end(); iter++) {
		(*iter)->render(camera, light);
	}
}

void WorldImpl::
add_body(Body3Ptr body)
{
	cout << "Add Body" << endl;
	bodies.push_back(body);
}

int WorldImpl::
tick()
{
	return 0;
}

} /* namespace domahony */
