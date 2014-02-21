/*
 * Die3.h
 *
 *  Created on: 2014-02-02
 *      Author: domahony
 */

#ifndef DIE3_H_
#define DIE3_H_

#include <vector>
#include <btBulletCollisionCommon.h>

namespace domahony {

class Die3 {
public:
	Die3();
	std::vector<float>& get_data() {
		return data;
	}

	float get_mass() const {
		return 10;
	}

	btCollisionShape * get_collision_shape() const {
		return new btBoxShape(btVector3(1,1,1));
	}

	virtual ~Die3();
private:
	std::vector<float> data;
};

} /* namespace domahony */
#endif /* DIE3_H_ */
