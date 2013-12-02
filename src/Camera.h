/*
 * Camera.h
 *
 *  Created on: 2013-06-17
 *      Author: domahony
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace domahony {
namespace framework {

class Camera {
public:
	Camera() :
		m_projection(glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f)),
		m_location(glm::vec3(0,2,6)),
		m_view(glm::lookAt(
				m_location,
				glm::vec3(0,0,0),
				glm::vec3(0,1,0))),
		m_quaternion(glm::quat_cast(m_view))
	{

		std::cout << "Matrix: " << glm::to_string(m_view) << std::endl;
		std::cout << "Quaternion: "
				<< glm::to_string(m_quaternion.x) << ", "
				<< glm::to_string(m_quaternion.y) << ", "
				<< glm::to_string(m_quaternion.z) << ", "
				<< glm::to_string(m_quaternion.w)
				<< std::endl;
		std::cout << "Matrix2: " << glm::to_string(view()) << std::endl;

		std::cout << "Location: " << glm::to_string(glm::vec4(m_location.x, m_location.y, m_location.z, 0) * glm::inverse(m_view)) << std::endl;

	}

	void update_perspective(const int& w, const int& h) {
		m_projection = glm::perspective(45.f, w/static_cast<float>(h), 0.1f, 100.0f);
	}

	const glm::mat4 view() const {
		return
				glm::mat4_cast(m_quaternion) *
				glm::translate(glm::mat4(1), m_location * -1.f);
	}

	const glm::mat4 projection() const {
		return m_projection;
	}

	const glm::vec3 location() const {
		return glm::vec3(glm::vec4(m_location, 0) * glm::inverse(m_view));
	}

	void left() {
		m_location += glm::vec3(-.1, 0, 0);
	}

	void right() {
		m_location += glm::vec3(.1, 0, 0);
	}

	void up() {
		m_location += glm::vec3(0, .1, 0);
	}

	void down() {
		m_location += glm::vec3(0, -.1, 0);
	}

	void in() {
		m_location += glm::vec3(0, 0, -.1);
	}

	void out() {
		m_location += glm::vec3(0, 0, .1);
	}

	void yaw_left() {

	}

	void yaw_right() {

	}

	void pitch_up() {

	}

	void pitch_down() {

	}

	void roll_left() {

	}

	void roll_right() {

	}

private:
	void setView() {

		//m_view = glm::lookAt(m_location, glm::vec3(0,0,0), glm::vec3(0,1,0));
		m_quaternion = glm::quat_cast(m_view);

		std::cout << "Quaternion: "
				<< glm::to_string(m_quaternion.x) << ", "
				<< glm::to_string(m_quaternion.y) << ", "
				<< glm::to_string(m_quaternion.z) << ", "
				<< glm::to_string(m_quaternion.w)
				<< std::endl;
		std::cout << "Matrix: " << glm::to_string(m_view) << std::endl;
	}

private:
	glm::mat4 m_projection;
	glm::vec3 m_location;
	glm::mat4 m_view;
	glm::quat m_quaternion;

};

} /* namespace framework */
} /* namespace domahony */
#endif /* CAMERA_H_ */
