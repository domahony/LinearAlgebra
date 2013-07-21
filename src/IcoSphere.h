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

namespace domahony {
namespace opengl {

class IcoSphere : public domahony::applications::Drawable {
public:
	IcoSphere(const glm::mat4&, const GLint& mvp);
	virtual ~IcoSphere();

	static const double phi;

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
#endif /* ICOSPHERE_H_ */
