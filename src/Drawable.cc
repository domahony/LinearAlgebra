/*
 * Drawable.cc
 *
 *  Created on: 2013-06-19
 *      Author: domahony
 */

#include "Drawable.h"
#include "OpenGL.h"
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
#include <CGAL/Cartesian.h>
#include <CGAL/Min_sphere_annulus_d_traits_3.h>
#include <CGAL/Min_sphere_d.h>

namespace domahony {
namespace applications {

typedef CGAL::Cartesian<GLfloat> K;
typedef CGAL::Min_sphere_annulus_d_traits_3<K> Traits;
typedef CGAL::Min_sphere_d<Traits> Min_sphere;
typedef K::Point_3 Point;



Drawable::
Drawable(const domahony::opengl::Program& program, const std::vector<GLfloat>& data, const glm::mat4& location,
		const domahony::framework::Material& m) :
		program(program), vbo(), location(location), material(m)
{
	vbo.buffer_data(data);

	std::vector<GLfloat>::const_iterator iter = data.begin();

	std::vector<Point> point;

	while (iter != data.end()) {

		GLfloat coord[3];
		coord[0] = *iter;
		iter++;
		coord[1] = *iter;
		iter++;
		coord[2] = *iter;
		iter++;

		point.push_back(Point(coord[0], coord[1], coord[2]));
	}

	Min_sphere ms(point.begin(), point.end());

	std::cout << "Center: " << ms.center() << std::endl;
	std::cout << "Radius: " << sqrt(ms.squared_radius()) << std::endl;
	//CGAL::set_pretty_mode(std::cout);
	//std::cout << ms;

	collisionShape = boost::shared_ptr<btCollisionShape>(new btSphereShape(sqrt(ms.squared_radius())));
	motionstate = boost::shared_ptr<btDefaultMotionState>(
			new btDefaultMotionState(btTransform())
	);

	btRigidBody::btRigidBodyConstructionInfo rbCI(0, motionstate.get(), collisionShape.get(), btVector3(0,0,0));

	rigidbody = boost::shared_ptr<btRigidBody>(new btRigidBody(rbCI));

}


void
Drawable::draw(const domahony::framework::Camera& c)
{
	/*
	 * draw something at this location
	 */
	program.set_eye_location(c.location());

	program.set_light_direction(c.get_light().get_direction());
	program.set_light_color(c.get_light().get_color());
	program.set_global_light(c.get_light().get_global());

	/*
	glm::mat4 mvp = c.projection() * c.view() * location;
	program.set_mvp_matrix(mvp);
	*/
	program.set_mvp_matrix(c.projection() * c.view() * location);

	/*
	glm::mat3 view = glm::mat3(c.view());
	program.set_view_matrix(view);
	*/
	program.set_view_matrix(glm::mat3(c.view()));

	program.set_specular_color(material.get_specular_color());
	program.set_gloss(material.get_gloss());

	vbo.bind();

	enableVertexAttributes();
	doDraw(c);

	disableVertexAttributes();

	std::cout << "Displayed Called" << std::endl;
}

} /* namespace applications */
} /* namespace domahony */
