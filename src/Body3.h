/*
 * Body3.h
 *
 *  Created on: 2014-01-29
 *      Author: domahony
 */

#ifndef BODY3_H_
#define BODY3_H_

#include "Camera.h"
#include "Light.h"
#include "Material.h"

#include <boost/shared_ptr.hpp>

namespace domahony {

class Body3 {
public:
	Body3(const glm::mat4& l): location(l), material(glm::vec3(.6), 1.f) {};

	virtual ~Body3() {};
	virtual void render(const domahony::framework::Camera& c, const domahony::framework::Light& l) const =0;

	void set_location(const glm::mat4& loc) {
		location = loc;
	}

	glm::mat4 get_location() const
	{
		return location;
	}

	domahony::framework::Material get_material() const
	{
		return material;
	}

private:
	glm::mat4 location;
	domahony::framework::Material material;
};

typedef boost::shared_ptr<Body3> Body3Ptr;

} /* namespace domahony */
#endif /* BODY3_H_ */
