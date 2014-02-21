/*
 * World.h
 *
 *  Created on: 2014-01-25
 *      Author: domahony
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <boost/shared_ptr.hpp>
#include "Body3.h"

namespace domahony {

class WorldImpl;

class World {
public:
	World();
	virtual ~World();

	void render();
	int tick();

	void reset();

	void move_camera(const glm::vec3&, const float&);
	void move_sight(const glm::vec2&);
	void look();

	void camera_in();
	void camera_out();
	glm::mat4 camera_location() const;
	glm::vec3 light_direction() const;
	glm::vec3 light_color() const;
	float global_light() const;


	void update_perspective(const int width, const int height);

	void add_body(Body3Ptr);
	glm::mat4 get_projection() const;
	glm::mat4 get_view() const;


private:
	boost::shared_ptr<WorldImpl> impl;
};

} /* namespace domahony */
#endif /* WORLD_H_ */
