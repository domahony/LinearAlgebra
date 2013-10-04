/*
 * ObjShape.h
 *
 *  Created on: 2013-06-24
 *      Author: domahony
 */

#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <vector>
#include "OpenGL.h"

namespace domahony {
namespace opengl {

class ObjParser {
private:
	ObjParser() {}
	virtual ~ObjParser() {}

public:
	static void get_data(const char*, std::vector<GLfloat>&);
};

} /* namespace opengl */
} /* namespace domahony */
#endif /* CUBE_H_ */
