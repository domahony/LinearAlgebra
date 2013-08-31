/*
 * ObjShape.h
 *
 *  Created on: 2013-06-24
 *      Author: domahony
 */

#ifndef OBJSHAPE_H_
#define OBJSHAPECUBE_H_

#include "Drawable.h"
#include "Program.h"
#include "Material.h"
#include <glm/glm.hpp>

namespace domahony {
namespace opengl {

class ObjShape: public domahony::applications::Drawable {
public:
	ObjShape(const domahony::opengl::Program&, const glm::mat4&, const domahony::framework::Material&);
	virtual ~ObjShape();

protected:
	virtual void enableVertexAttributes() const;
	virtual void doDraw(const domahony::framework::Camera&) const;
	virtual void disableVertexAttributes() const;

private:
	VBO idx;
	int npoints;

};

} /* namespace opengl */
} /* namespace domahony */
#endif /* CUBE_H_ */
