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
#include "Crosshair.h"
#include "Camera.h"
#include "Light.h"
#include <vector>

namespace domahony {

template<class Creator, class Renderer>
Body4<Creator, Renderer>::
Body4(const glm::mat4& l) : Body3(l), creator(new Creator()), renderer(new Renderer()) {
	renderer->set_data(creator->get_data());
}

template<class Creator, class Renderer>
void Body4<Creator, Renderer>::
render(const domahony::framework::Camera& c, const domahony::framework::Light& l) const {

	renderer->enable();
	renderer->set_eye_location(c.location());

	renderer->set_light_direction(l.get_direction());
	renderer->set_light_color(l.get_color());
	renderer->set_global_light(l.get_global());

	renderer->set_mvp_matrix(c.projection()
	* c.view()
	* get_location()
	* glm::scale(glm::mat4(1.f), glm::vec3(1.0))
	);

	renderer->set_view_matrix(glm::mat3(c.view()));

	renderer->set_normal_matrix(glm::mat3(c.projection() * c.view() * get_location()));

	renderer->set_specular_color(get_material().get_specular_color());
	renderer->set_gloss(get_material().get_gloss());

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
template class domahony::Body4<domahony::Circle, domahony::Crosshair>;
