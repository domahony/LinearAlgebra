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
		location(glm::vec3(4,3,3)),
		m_view(glm::lookAt(
				location,
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

	void left() {location 	+= glm::vec3(-.1, 0, 0); setView();}
	void right() {location 	+= glm::vec3(.1, 0, 0); setView();}

	void up() {location 	+= glm::vec3(0, .1, 0); setView();}
	void down() {location 	+= glm::vec3(0, -.1, 0); setView();}

	void in() {location 	+= glm::vec3(0, 0, -.1); setView();}
	void out() {location 	+= glm::vec3(0, 0, .1); setView();}

private:
	void setView() {
		m_view = glm::lookAt(location, glm::vec3(0,0,0), glm::vec3(0,1,0));
	}

private:
	glm::mat4 m_projection;
	glm::vec3 location;
	glm::mat4 m_view;

};

} /* namespace framework */
} /* namespace domahony */
#endif /* CAMERA_H_ */
