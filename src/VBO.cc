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

VBO::VBO(const GLenum& type) : type(type), vbo(generate_vbo()), buffer_size(0){
}

VBO::~VBO() {
	// TODO Auto-generated destructor stub
}


template<typename T>
int VBO::
buffer_data(const std::vector<T>& data)
{
	glBindBuffer(type, vbo);
	glBufferData(type, data.size() * sizeof(T), &data[0], GL_STATIC_DRAW);
	glBindBuffer(type, 0);

	buffer_size = data.size();

	return 1;
}

template int VBO::buffer_data<GLfloat>(const std::vector<GLfloat>&);
template int VBO::buffer_data<GLbyte>(const std::vector<GLbyte>&);
template int VBO::buffer_data<GLushort>(const std::vector<GLushort>&);
template int VBO::buffer_data<GLuint>(const std::vector<GLuint>&);

} /* namespace opengl */
} /* namespace domahony */
