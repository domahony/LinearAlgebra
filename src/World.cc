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
move_sight(const glm::vec2& v)
{
	impl->move_sight(v);
}

void World::
move_camera(const glm::vec3& v, const float& d)
{
	impl->move_camera(v, d);
}

void World::
camera_out()
{
	impl->camera_out();
}

void World::
camera_in()
{
	impl->camera_in();
}

void World::
update_perspective(const int width, const int height)
{
	impl->update_perspective(width, height);
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

glm::mat4 World::
get_projection() const {
	return impl->get_projection();
}

glm::mat4 World::
get_view() const {
	return impl->get_view();
}

World::~World() {
	// TODO Auto-generated destructor stub
}

} /* namespace domahony */
