/*
 * VBO.h
 *
 *  Created on: 2013-06-15
 *      Author: domahony
 */

#ifndef VBO_H_
#define VBO_H_

#include <vector>
#include "OpenGL.h"

namespace domahony {
namespace opengl {

class VBO {
public:
	VBO(const GLenum& type=GL_ARRAY_BUFFER);
	virtual ~VBO();

	operator GLuint () const {
		return vbo;
	}

	void bind() const {
		glBindBuffer(type, vbo);
	}


	template<typename T>
	int buffer_data(const std::vector<T>& data);

private:
	GLenum type;
	GLuint vbo;
};

} /* namespace opengl */
} /* namespace domahony */
#endif /* VBO_H_ */
