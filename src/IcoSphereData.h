/*
 * IcoSphereData.h
 *
 *  Created on: 2013-09-26
 *      Author: domahony
 */

#ifndef ICOSPHEREDATA_H_
#define ICOSPHEREDATA_H_

#include "OpenGL.h"
#include <vector>

namespace domahony {
namespace framework {

class IcoSphereData {
public:
	IcoSphereData();
	virtual ~IcoSphereData();

	static std::vector<GLfloat> get_data();

	static const double phi;
};


} /* namespace framework */
} /* namespace domahony */
#endif /* ICOSPHEREDATA_H_ */
