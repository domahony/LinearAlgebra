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
move_camera(const glm::vec3& v, const float& d)
{
	camera.move(v, d);
}

void WorldImpl::
move_sight(const glm::vec2& v)
{
	bodies[bodies.size() - 1]->move(glm::vec3(v.x, v.y, 0));
}

void WorldImpl::
camera_in()
{
	camera.in();
}

void WorldImpl::
camera_out()
{
	camera.out();
}

void WorldImpl::
update_perspective(const int width, const int height)
{
	camera.update_perspective(width, height);
}

void WorldImpl::
render()
{
	cout << "Render" << endl;
	for (std::vector<Body3Ptr>::const_iterator iter = bodies.begin(); iter != bodies.end(); iter++) {
		(*iter)->render(camera, light, camera.get_width(), camera.get_height());
	}
}

glm::mat4 WorldImpl::
get_projection() const
{
	return camera.projection();
}

glm::mat4 WorldImpl::
get_view() const
{
	return camera.view();
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
