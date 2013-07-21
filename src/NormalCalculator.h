/*
 * NormalCalculator.h
 *
 *  Created on: 2013-07-11
 *      Author: domahony
 */

#ifndef NORMALCALCULATOR_H_
#define NORMALCALCULATOR_H_

#include <glm/glm.hpp>

namespace domahony {
namespace framework {

class NormalCalculator {
public:
	NormalCalculator() : idx(-1) {

	}

	virtual ~NormalCalculator() {

	}

	void next(const glm::vec3& vec) {
		idx = (idx + 1) % 3;
		tri[idx].x = vec.x;
		tri[idx].y = vec.y;
		tri[idx].z = vec.z;
	}

	const glm::vec3 normal() const {
		glm::vec3 u = tri[1] - tri[0];
		glm::vec3 v = tri[2] - tri[0];

		glm::vec3 n(
				u.y * v.z - u.z * v.y,
				u.z * v.x - u.x * v.z,
				u.x * v.y - u.y * v.x
		);

		return n;
	}

private:
	glm::vec3 tri[3];
	unsigned char idx;

};

} /* namespace framework */
} /* namespace domahony */
#endif /* NORMALCALCULATOR_H_ */
