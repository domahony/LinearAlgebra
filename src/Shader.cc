/*
 * Shader.cc
 *
 *  Created on: 2013-06-08
 *      Author: domahony
 */

#include "OpenGL.h"
#include "Shader.h"

namespace domahony {
namespace opengl {

Shader::Shader(const GLenum& type, const std::string& fname) : shader(create_shader(type, fname)) {

}

Shader::~Shader() {
	// TODO Auto-generated destructor stub
}

} /* namespace opengl */
} /* namespace domahony */
