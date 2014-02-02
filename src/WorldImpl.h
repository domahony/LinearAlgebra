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

	void render();
	int tick();

	void add_body(Body3Ptr);

private:
	std::vector<Body3Ptr> bodies;
	domahony::framework::Camera camera;
	domahony::framework::Light light;
};

} /* namespace domahony */
#endif /* WORLDIMPL_H_ */
