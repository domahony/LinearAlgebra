/*
 * Circle.cc
 *
 *  Created on: 2014-02-09
 *      Author: domahony
 */

#include "Circle.h"
#include "ObjParser.h"

namespace domahony {

#ifdef __cplusplus
extern "C" {
#endif

extern const char circle[];

#ifdef __cplusplus
}
#endif

Circle::Circle() {
	domahony::opengl::ObjParser::get_data(circle, 0, data);
}

Circle::~Circle() {
	// TODO Auto-generated destructor stub
}

} /* namespace domahony */
