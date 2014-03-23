/*
 * Body4.cc
 *
 *  Created on: 2014-02-01
 *      Author: domahony
 */

#include "Body4.h"
#include "Die3.h"
#include "Circle.h"
#include "OpenGLState.h"
#include "OpenGLState2.h"
#include "Crosshair.h"
#include "GroundPlane.h"
#include "Plane.h"
#include "Camera.h"
#include "Light.h"
#include "Light2.h"
#include <vector>

namespace domahony {

template<class Creator, class Renderer>
Body4<Creator, Renderer>::
Body4(boost::shared_ptr<Creator> c, const glm::mat4& l) : Body3(l, c->get_mass(), c->get_collision_shape()), creator(c), renderer(new Renderer()) {
	renderer->set_data(creator->get_data());
}

template<class Creator, class Renderer>
void Body4<Creator, Renderer>::
render(const domahony::framework::Camera& c, const domahony::framework::Light& l, const int w, const int h) const {

	renderer->enable();
	//renderer->set_eye_location(c.location());

	domahony::Light2 light2(l.get_direction(), l.get_color(), l.get_color());
	renderer->set_light(c.location(), light2);

	//renderer->set_light_direction(l.get_direction());
	//renderer->set_light_color(l.get_color());
	//renderer->set_global_light(l.get_global());

	glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(
					h/static_cast<float>(w * 4),
					1/static_cast<float>(4),
					1/static_cast<float>(4)));

	glm::mat4 translate = glm::translate(glm::mat4(1), glm::vec3(0.5, 0, 0));

	//renderer->set_projection_matrix(scale * get_location());
	renderer->set_projection_matrix(c.projection());

	renderer->set_modelview_matrix(
	c.view()
	* get_location()
	* glm::scale(glm::mat4(1.f), glm::vec3(1.0))
	);

	//renderer->set_view_matrix(glm::mat3(c.view()));

	renderer->set_normal_matrix(glm::mat3(c.projection() * c.view() * get_location()));

	//renderer->set_specular_color(get_material().get_specular_color());
	//renderer->set_gloss(get_material().get_gloss());

	renderer->render();
	renderer->disable();
}

template<class Creator, class Renderer>
Body4<Creator, Renderer>::
~Body4() {
	// TODO Auto-generated destructor stub
}

} /* namespace domahony */
template class domahony::Body4<domahony::Die3, domahony::OpenGLState>;
//template class domahony::Body4<domahony::Circle, domahony::Crosshair>;
//template class domahony::Body4<domahony::Plane, domahony::Crosshair>;
template class domahony::Body4<domahony::Plane, domahony::OpenGLState>;
//template class domahony::Body4<domahony::Plane, domahony::OpenGLState2>;
