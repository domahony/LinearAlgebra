/*
 * Body4.h
 *
 *  Created on: 2014-02-01
 *      Author: domahony
 */

#ifndef BODY4_H_
#define BODY4_H_

#include "Body3.h"
#include "World.h"

namespace domahony {

template<class Creator, class Renderer>
class Body4 : public Body3 {
public:
	Body4(boost::shared_ptr<Creator>, const glm::mat4& location);
	void render(const domahony::framework::Camera& c, const domahony::framework::Light& l, const int w, const int h) const;

	virtual ~Body4();
private:
	boost::shared_ptr<Creator> creator;
	boost::shared_ptr<Renderer> renderer;

};

} /* namespace domahony */
#endif /* BODY4_H_ */
