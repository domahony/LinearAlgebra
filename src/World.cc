/*
 * World.cc
 *
 *  Created on: 2014-01-25
 *      Author: domahony
 */

#include "World.h"
#include "WorldImpl.h"

namespace domahony {

World::World() : impl(new WorldImpl())
{
	// TODO Auto-generated constructor stub

}

void World::
render()
{
	impl->render();
}

int World::
tick()
{
	return impl->tick();
}

void World::
add_body(Body3Ptr b)
{
	impl->add_body(b);
}

World::~World() {
	// TODO Auto-generated destructor stub
}

} /* namespace domahony */
