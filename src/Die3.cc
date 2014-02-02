/*
 * Die3.cc
 *
 *  Created on: 2014-02-02
 *      Author: domahony
 */

#include "Die3.h"
#include "ObjParser.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const char die4[];
extern const char die4_mtl[];
extern char Basic_Frag[];
extern char Basic_Vert[];

#ifdef __cplusplus
}
#endif

namespace domahony {

Die3::Die3() {
	domahony::opengl::ObjParser::get_data(die4, die4_mtl, data);
}

Die3::~Die3() {
	// TODO Auto-generated destructor stub
}

} /* namespace domahony */
