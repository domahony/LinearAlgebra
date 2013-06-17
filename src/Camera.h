/*
 * Camera.h
 *
 *  Created on: 2013-06-17
 *      Author: domahony
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace domahony {
namespace framework {

class Camera {
public:
	Camera() :
		m_projection(glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f)),
		m_view(glm::lookAt(
				glm::vec3(.25,.75,.5),
				glm::vec3(0,0,0),
				glm::vec3(0,1,0)))
	{

	}

	const glm::mat4 view() const {
		return m_view;
	}

	const glm::mat4 projection() const {
		return m_projection;
	}


private:
	glm::mat4 m_view;
	glm::mat4 m_projection;
};

} /* namespace framework */
} /* namespace domahony */
#endif /* CAMERA_H_ */
