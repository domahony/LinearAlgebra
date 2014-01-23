/*
 * SphereListCreator.h
 *
 *  Created on: 2013-12-15
 *      Author: domahony
 */

#ifndef SPHERELISTCREATOR_H_
#define SPHERELISTCREATOR_H_

#include <glm/glm.hpp>
#include <vector>

namespace domahony {
namespace framework {

class SphereListCreator {

public:
struct Sphere {
	glm::vec3 center;
	float radius;
};

public:
	static std::vector<Sphere> getSphereList(const int& nSpheres, 
	const int& maxRadius, const glm::ivec3& low, const glm::ivec3& high);

private:
	SphereListCreator();
	virtual ~SphereListCreator();
};

} /* namespace framework */
} /* namespace domahony */
#endif /* SPHERELISTCREATOR_H_ */
