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
#include "Material.h"
#include "Program.h"
#include <map>
#include <stack>

namespace domahony {
namespace applications {

class Drawable {
public:
	Drawable(const domahony::opengl::Program& program, const std::vector<GLfloat>& data, const glm::mat4& location,
			const domahony::framework::Material& m);
	void draw(const domahony::framework::Camera&);

	virtual ~Drawable() {}

	void push_location(const glm::mat4& l) {
		location.push(location.top() * l);
	}

	void pop_location() {
		location.pop();
	}

	glm::mat4 get_location() const {
		return location.top();
	}

protected:
	virtual void enableVertexAttributes() const = 0;
	virtual void doDraw(const domahony::framework::Camera&) = 0;
	virtual void disableVertexAttributes() const = 0;
	domahony::opengl::Program program;

private:
	domahony::opengl::VBO vbo;
	domahony::framework::Material material;

	std::stack<glm::mat4> location;

};

} /* namespace applications */
} /* namespace domahony */
#endif /* DRAWABLE_H_ */
