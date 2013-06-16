/*
 * Program.h
 *
 *  Created on: 2013-06-08
 *      Author: domahony
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "Shader.h"

namespace domahony {
namespace opengl {

class Program {
public:
	Program();
	void attach_shader(const Shader& shader);
	void link();

	operator GLint () const {
		return program;
	}

	virtual ~Program();

private:
	const GLint program;

};

} /* namespace opengl */
} /* namespace domahony */
#endif /* PROGRAM_H_ */
