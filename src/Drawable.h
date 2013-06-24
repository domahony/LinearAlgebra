/*
 * Drawable.h
 *
 *  Created on: 2013-06-19
 *      Author: domahony
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "Camera.h"
#include "OpenGL.h"
#include "VBO.h"

namespace domahony {
namespace applications {

class Drawable {
public:
	Drawable(const std::vector<GLfloat>& data, const glm::mat4& location, const GLint& mvp);
	void draw(const domahony::framework::Camera&);

	virtual ~Drawable() {}

protected:
	virtual void enableVertexAttributes() const = 0;
	virtual void doDraw() const = 0;
	virtual void disableVertexAttributes() const = 0;

private:
	const GLint mvp;
	glm::mat4 location;
	domahony::opengl::VBO vbo;

};

} /* namespace applications */
} /* namespace domahony */
#endif /* DRAWABLE_H_ */
