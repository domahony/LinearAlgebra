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

namespace domahony {
namespace applications {

class Drawable {
public:
	Drawable(const GLint& mvp): mvp(mvp) {}

	virtual void draw(const domahony::framework::Camera&) const = 0;
	virtual ~Drawable() {}

protected:
	const GLint mvp;


};

} /* namespace applications */
} /* namespace domahony */
#endif /* DRAWABLE_H_ */
