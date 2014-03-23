/*
 * Light2.h
 *
 *  Created on: Mar 23, 2014
 *      Author: domahony
 */

#ifndef LIGHT2_H_
#define LIGHT2_H_

#include <glm/glm.hpp>

namespace domahony {

class Light2 {
public:
	Light2(const glm::vec3& position, const glm::vec3& diffuse, const glm::vec3& specular) :
		position(position), diffuse(diffuse), specular(specular)
	{

	}
	virtual ~Light2()
	{

	}

	glm::vec3 get_position() const {
		return position;
	}

	glm::vec3 get_diffuse() const {
		return diffuse;
	}

	glm::vec3 get_specular() const {
		return specular;
	}
private:
	glm::vec3 position;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

} /* namespace domahony */

#endif /* LIGHT2_H_ */
