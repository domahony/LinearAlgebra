/*
 * RandomDiceBody.h
 *
 *  Created on: Feb 20, 2014
 *      Author: domahony
 */

#ifndef RANDOMDICEBODY_H_
#define RANDOMDICEBODY_H_

#include "Body4.h"
#include "Die3.h"
#include "OpenGLState.h"

namespace domahony {

class RandomDiceBody: public domahony::Body4<domahony::Die3, domahony::OpenGLState> {
public:
	RandomDiceBody(boost::shared_ptr<domahony::Die3> die);
	void reset();
	void activate();
	virtual ~RandomDiceBody();
};

} /* namespace domahony */

#endif /* RANDOMDICEBODY_H_ */
