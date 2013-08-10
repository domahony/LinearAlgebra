/*
 * Cube.h
 *
 *  Created on: 2013-06-24
 *      Author: domahony
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "Drawable.h"
#include "Program.h"
#include "Material.h"
#include <glm/glm.hpp>

namespace domahony {
namespace opengl {

class Cube: public domahony::applications::Drawable {
public:
	Cube(const domahony::opengl::Program&, const glm::mat4&, const domahony::framework::Material&);
	virtual ~Cube();

protected:
	virtual void enableVertexAttributes() const;
	virtual void doDraw(const domahony::framework::Camera&);
	virtual void disableVertexAttributes() const;

private:
	VBO idx;

};

} /* namespace opengl */
} /* namespace domahony */
#endif /* CUBE_H_ */
