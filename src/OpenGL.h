/*
 * OpenGL.h
 *
 *  Created on: 2013-06-06
 *      Author: domahony
 */

#ifndef OPENGL_H_
#define OPENGL_H_

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include <gl.h>
#include <string>

namespace domahony {

namespace opengl {

GLint create_shader(GLenum type, const std::string& fname);

}

}


#endif /* OPENGL_H_ */
