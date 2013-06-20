/*
 * Triangles.h
 *
 *  Created on: 2013-06-15
 *      Author: domahony
 */

#ifndef TRIANGLES_H_
#define TRIANGLES_H_

#include "Program.h"
#include "VBO.h"
#include "Camera.h"
#include "Drawable.h"
#include <glm/glm.hpp>

namespace domahony {
namespace opengl {

using domahony::framework::Camera;

class Triangles: public domahony::applications::Drawable {
public:
	Triangles(const GLint& mvp);

	virtual ~Triangles();
protected:
	void draw(const Camera&) const;

private:
	VBO vbo1;
	glm::mat4 model;
};

} /* namespace opengl */
} /* namespace domahony */
#endif /* TRIANGLES_H_ */
