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
		return glm::vec3(glm::vec4(m_location, 0));// * (m_view));
	}

	glm::vec3 move(const glm::vec3& v, const float& m) const {
		// use the rotation quaternion orientation to get the direction to move in
		return glm::vec3( (view() * glm::vec4(v.x, v.y, v.z, 0)) * 1);
	}

	glm::vec3 move2(const glm::vec3& v, const float& m) {

		glm::vec3 v2 = glm::mat3(glm::inverse(view())) * v;

		glm::mat4 t = glm::translate(glm::mat4(1.f), v2);

		glm::vec4 n = t * glm::vec4(m_location.x, m_location.y, m_location.z, 1.f);

		m_location = glm::vec3(n);
		return v;
	}

	void left() {
		//m_location += move(glm::vec3(-.1, 0, 0), -1);
		move2(glm::vec3(-.1, 0, 0), -1);
	}

	void right() {
		//m_location += move(glm::vec3(.1, 0, 0), 1);
		move2(glm::vec3(.1, 0, 0), 1);
	}

	void up() {
		//m_location += move(glm::vec3(0,.1, 0), 1);
		move2(glm::vec3(0,.1, 0), 1);
	}

	void down() {
		//m_location += move(glm::vec3(0,-.1, 0), -1);
		move2(glm::vec3(0,-.1, 0), -1);
	}

	void in() {
		//m_location += move(glm::vec3(0, 0, -.1), -1);
		move2(glm::vec3(0, 0, -.1), -1);
	}

	void out() {
		//m_location += move(glm::vec3(0, 0, .1), 1);
		move2(glm::vec3(0, 0, .1), 1);
	}




	glm::quat spin(const glm::vec3& v, const float& a) const {
		glm::vec3 axis(glm::mat3(glm::inverse(view())) * v);
		glm::quat local = glm::angleAxis(a, axis);
		return local;
	}

	void yaw_left() {
		m_quaternion = m_quaternion * spin(glm::vec3(0, 1, 0), 2.f);
	}

	void yaw_right() {
		m_quaternion = m_quaternion * spin(glm::vec3(0, 1, 0), -2.f);
	}

	void pitch_up() {
		m_quaternion = m_quaternion * spin(glm::vec3(1, 0, 0), 2.f);
	}

	void pitch_down() {
		m_quaternion = m_quaternion * spin(glm::vec3(1, 0, 0), -2.f);
	}

	void roll_left() {
		m_quaternion = m_quaternion * spin(glm::vec3(0, 0, 1), -2.f);
	}

	void roll_right() {
		m_quaternion = m_quaternion * spin(glm::vec3(0, 0, 1), 2.f);
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
