/*
 * Circle.h
 *
 *  Created on: 2014-02-09
 *      Author: domahony
 */

#ifndef PLANE_H_
#define PLANE_H_

#include <vector>
#include <btBulletCollisionCommon.h>
#include <glm/glm.hpp>

namespace domahony {

class Plane {
public:
	Plane(glm::vec3 normal=glm::vec3(0,1,0), float constant=1);
	virtual ~Plane();

	std::vector<float>& get_data() {
		return data;
	}

	float get_mass() const {
		return 0;
	}

	btCollisionShape * get_collision_shape() const {
		return cshape;
	}

private:
	btCollisionShape *cshape;
	std::vector<float> data;
};

} /* namespace domahony */
#endif /* CIRCLE_H_ */
