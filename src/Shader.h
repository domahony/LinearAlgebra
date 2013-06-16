/*
 * Shader.h
 *
 *  Created on: 2013-06-08
 *      Author: domahony
 */

#ifndef SHADER_H_
#define SHADER_H_

#include "OpenGL.h"

namespace domahony {
namespace opengl {

class Shader {
public:
	Shader(const GLenum& type, const std::string&fname);
	virtual ~Shader();

	 operator GLint() const {
		return shader;
	}

private:
	GLint shader;
};

} /* namespace opengl */
} /* namespace domahony */
#endif /* SHADER_H_ */
