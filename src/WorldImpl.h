/*
 * WorldImpl.h
 *
 *  Created on: 2014-01-25
 *      Author: domahony
 */

#ifndef WORLDIMPL_H_
#define WORLDIMPL_H_

#include "Body3.h"
#include <vector>

namespace domahony {

class WorldImpl {
public:
	WorldImpl();
	virtual ~WorldImpl();

	void update_perspective(const int width, const int height);
	void move_camera(const glm::vec3&, const float&);
	void move_sight(const glm::vec2&);
	void look();
	void camera_in();
	void camera_out();
	void render();
	int tick();

	glm::mat4 get_projection() const;
	glm::mat4 get_view() const;

	void add_body(Body3Ptr);

private:
	std::vector<Body3Ptr> bodies;
	domahony::framework::Camera camera;
	domahony::framework::Light light;
};

} /* namespace domahony */
#endif /* WORLDIMPL_H_ */
