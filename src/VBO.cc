/*
 * VBO.cc
 *
 *  Created on: 2013-06-15
 *      Author: domahony
 */

#include <iostream>
#include "VBO.h"

namespace domahony {
namespace opengl {

static GLuint
generate_vbo()
{
	GLuint ret;
	glGenBuffers(1, &ret);
	return ret;
}

VBO::VBO() : vbo(generate_vbo()){
}

VBO::~VBO() {
	// TODO Auto-generated destructor stub
}


template<typename T>
int VBO::
buffer_data(const std::vector<T>& data)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), &data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template int VBO::buffer_data<GLfloat>(const std::vector<GLfloat>&);
template int VBO::buffer_data<GLbyte>(const std::vector<GLbyte>&);

} /* namespace opengl */
} /* namespace domahony */
