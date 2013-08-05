/*
 * Sphere.h
 *
 *  Created on: 2013-06-24
 *      Author: domahony
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Drawable.h"
#include "VBO.h"

namespace domahony {
namespace opengl {

class Sphere: public domahony::applications::Drawable {
public:
	Sphere(const std::map<std::string, GLint>& uniform);
	virtual ~Sphere();

protected:
	virtual void enableVertexAttributes() const;
	virtual void doDraw() const;
	virtual void disableVertexAttributes() const;

private:
	VBO idx;
	int nverts;
	int idx_size;
};

} /* namespace opengl */
} /* namespace domahony */
#endif /* SPHERE_H_ */
