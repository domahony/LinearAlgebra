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
		m_location(glm::vec3(0,2,10)),
		m_view(glm::lookAt(
				m_location,
				glm::vec3(0,0,0),
				glm::vec3(0,1,0)))
	{

	}

	void update_perspective(const int& w, const int& h) {
		m_projection = glm::perspective(45.f, w/static_cast<float>(h), 0.1f, 100.0f);
	}

	const glm::mat4 view() const {
		return m_view;
	}

	const glm::mat4 projection() const {
		return m_projection;
	}

	const glm::vec3 location() const {
		return m_location;
	}

	void left() {m_location 	+= glm::vec3(-.1, 0, 0); setView();}
	void right() {m_location 	+= glm::vec3(.1, 0, 0); setView();}

	void up() {m_location 	+= glm::vec3(0, .1, 0); setView();}
	void down() {m_location 	+= glm::vec3(0, -.1, 0); setView();}

	void in() {m_location 	+= glm::vec3(0, 0, -.1); setView();}
	void out() {m_location 	+= glm::vec3(0, 0, .1); setView();}

private:
	void setView() {
		m_view = glm::lookAt(m_location, glm::vec3(0,0,0), glm::vec3(0,1,0));
	}

private:
	glm::mat4 m_projection;
	glm::vec3 m_location;
	glm::mat4 m_view;

};

} /* namespace framework */
} /* namespace domahony */
#endif /* CAMERA_H_ */
