/*
 * Sphere.h
 *
 *  Created on: 2013-06-24
 *      Author: domahony
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Drawable.h"

namespace domahony {
namespace opengl {

class Sphere: public domahony::applications::Drawable {
public:
	Sphere(const glm::mat4&, const GLint& mvp);
	virtual ~Sphere();

protected:
	virtual void enableVertexAttributes() const;
	virtual void doDraw() const;
	virtual void disableVertexAttributes() const;

private:
	int nverts;
};

} /* namespace opengl */
} /* namespace domahony */
#endif /* SPHERE_H_ */
