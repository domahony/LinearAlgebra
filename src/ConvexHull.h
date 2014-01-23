/*
 * ConvexHull.h
 *
 *  Created on: 2013-12-18
 *      Author: domahony
 */

#ifndef CONVEXHULL_H_
#define CONVEXHULL_H_

#include "OpenGL.h"
#include "Physics.h"
#include "SphereListCreator.h"

namespace domahony {
namespace opengl {

class ConvexHull {
private:
	ConvexHull();
	virtual ~ConvexHull();

public:

	static void get_data(
			std::vector<domahony::framework::SphereListCreator::Sphere>::iterator begin,
			std::vector<domahony::framework::SphereListCreator::Sphere>::iterator end,
			std::vector<GLfloat>& data,
			glm::vec3& centroid);

	static void get_data(
			std::vector<domahony::physics::Physics::ContactInfoItem>::iterator begin,
			std::vector<domahony::physics::Physics::ContactInfoItem>::iterator end,
			std::vector<GLfloat>& data,
			glm::vec3& centroid);

};

} /* namespace opengl */
} /* namespace domahony */
#endif /* CONVEXHULL_H_ */
