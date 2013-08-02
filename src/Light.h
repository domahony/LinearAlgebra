/*
 * Light.h
 *
 *  Created on: 2013-08-02
 *      Author: domahony
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <glm/glm.hpp>

namespace domahony {
namespace framework {

class Light {
public:
	Light(const glm::vec3& direction, const glm::vec3& color) : direction(direction), color(color)
	{

	}
	virtual ~Light() {

	}

	glm::vec3 get_direction() const {
		return direction;
	}

	glm::vec3 get_color() const {
		return color;
	}

	void up() {
		direction = glm::vec3(0,10,0);
	}

	void down() {
		direction = glm::vec3(0,-10,0);
	}

	void left() {
		direction = glm::vec3(-10,0,0);
	}

	void right() {
		direction = glm::vec3(10,0,0);
	}

	void in() {
		direction = glm::vec3(0,0,-10);
	}

	void out() {
		direction = glm::vec3(0,0,10);
	}

private:
	glm::vec3 direction;
	glm::vec3 color;
};

} /* namespace framework */
} /* namespace domahony */
#endif /* LIGHT_H_ */
