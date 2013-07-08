/*
 * Cube.h
 *
 *  Created on: 2013-06-24
 *      Author: domahony
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "Drawable.h"
#include <glm/glm.hpp>

namespace domahony {
namespace opengl {

class Cube: public domahony::applications::Drawable {
public:
	Cube(const glm::mat4& location, const GLint& mvp);
	virtual ~Cube();

protected:
	virtual void enableVertexAttributes() const;
	virtual void doDraw() const;
	virtual void disableVertexAttributes() const;

private:
	VBO idx;

};

} /* namespace opengl */
} /* namespace domahony */
#endif /* CUBE_H_ */
