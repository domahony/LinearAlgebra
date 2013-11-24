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
	Light(const glm::vec3& direction, const glm::vec3& color, const float& global) : direction(direction), color(color), global(global)
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

	void set_global(const float& g) {
		global = g;
	}

	float get_global() const {
		return global;
	}

	void up() {
		direction += glm::vec3(0,2,0);
	}

	void down() {
		direction += glm::vec3(0,-2,0);
	}

	void left() {
		direction += glm::vec3(2,0,0);
	}

	void right() {
		direction += glm::vec3(2,0,0);
	}

	void in() {
		direction += glm::vec3(0,0,-2);
	}

	void out() {
		direction += glm::vec3(0,0,2);
	}

private:
	glm::vec3 direction;
	glm::vec3 color;
	float global;
};

} /* namespace framework */
} /* namespace domahony */
#endif /* LIGHT_H_ */
