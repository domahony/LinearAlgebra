/*
 * Plane.cc
 *
 *  Created on: 2014-02-09
 *      Author: domahony
 */

#include "Plane.h"
#include "ObjParser.h"
#include "glm/glm.hpp"

namespace domahony {

#ifdef __cplusplus
extern "C" {
#endif

extern const char plane[];

#ifdef __cplusplus
}
#endif

Plane::Plane(glm::vec3 normal, float constant) : cshape(new btStaticPlaneShape(btVector3(normal.x,normal.y,normal.z),constant)) {
	domahony::opengl::ObjParser::get_data(plane, 0, data);
}

Plane::~Plane() {
	// TODO Auto-generated destructor stub
}

} /* namespace domahony */
