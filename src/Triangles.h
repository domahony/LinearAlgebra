/*
 * Triangles.h
 *
 *  Created on: 2013-06-15
 *      Author: domahony
 */

#ifndef TRIANGLES_H_
#define TRIANGLES_H_

#include "Drawable.h"
#include <glm/glm.hpp>

namespace domahony {
namespace opengl {

class Triangles: public domahony::applications::Drawable {
public:
	Triangles(const glm::mat4& location, const GLint& mvp);
	virtual ~Triangles();

protected:
	virtual void enableVertexAttributes() const;
	virtual void doDraw() const;
	virtual void disableVertexAttributes() const;

};

} /* namespace opengl */
} /* namespace domahony */
#endif /* TRIANGLES_H_ */
