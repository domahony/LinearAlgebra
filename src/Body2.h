/*
 * Body2.h
 *
 *  Created on: 2014-01-26
 *      Author: domahony
 */

#ifndef BODY2_H_
#define BODY2_H_

#include <boost/shared_ptr.hpp>

namespace domahony {


class Body2Impl;

class Body2 {
public:
	Body2();
	virtual ~Body2();
	virtual void render();

private:
	boost::shared_ptr<Body2Impl> impl;

};

typedef boost::shared_ptr<Body2> BodyPtr;

} /* namespace domahony */
#endif /* BODY2_H_ */
