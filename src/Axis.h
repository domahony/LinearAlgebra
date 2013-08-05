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

class Axis: public domahony::applications::Drawable {

public:
	Axis(const glm::mat4& location, const std::map<std::string, GLint>& uniform);
	virtual ~Axis();

protected:
	virtual void enableVertexAttributes() const;
	virtual void doDraw() const;
	virtual void disableVertexAttributes() const;

};
} /* namespace opengl */
} /* namespace domahony */
#endif /* AXIS_H_ */
