/*
 * Triangles.h
 *
 *  Created on: 2013-06-15
 *      Author: domahony
 */

#ifndef AXIS_H_
#define AXIS_H_

#include "Program.h"
#include "VBO.h"
#include "Camera.h"
#include "Drawable.h"
#include <glm/glm.hpp>

namespace domahony {
namespace opengl {

using domahony::framework::Camera;

class Axis: public domahony::applications::Drawable {
public:
	Axis(const GLint& mvp);

	virtual ~Axis();
protected:
	void draw(const Camera&) const;

private:
	VBO vbo1;
	glm::mat4 model;
};

} /* namespace opengl */
} /* namespace domahony */
#endif /* AXIS_H_ */
