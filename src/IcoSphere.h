/*
 * IcoSphere.h
 *
 *  Created on: 2013-07-17
 *      Author: domahony
 */

#ifndef ICOSPHERE_H_
#define ICOSPHERE_H_

#include <glm/glm.hpp>
#include "Drawable.h"
#include "Material.h"

namespace domahony {
namespace opengl {

class IcoSphere : public domahony::applications::Drawable {
public:
	IcoSphere(const domahony::opengl::Program& program, const glm::mat4&, const domahony::framework::Material& material, const int& resolution);
	virtual ~IcoSphere();

	static const double phi;

protected:
	virtual void enableVertexAttributes() const;
	virtual void doDraw(const domahony::framework::Camera&) const;
	virtual void disableVertexAttributes() const;

private:
	VBO idx;
	int nverts;
	int idx_size;
	int resolution;

};

} /* namespace opengl */
} /* namespace domahony */
#endif /* ICOSPHERE_H_ */
