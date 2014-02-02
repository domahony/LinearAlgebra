/*
 * Die2.h
 *
 *  Created on: 2014-01-29
 *      Author: domahony
 */

#ifndef DIE2_H_
#define DIE2_H_
#include "Program.h"
#include "Body3.h"
#include <boost/shared_ptr.hpp>

namespace domahony {

class Die2 {
public:
	Die2() : program() {
		init();
	};

	void init();

	void render() const;

	virtual ~Die2() {};

private:
	domahony::opengl::Program program;
};

typedef boost::shared_ptr<Die2> Die2Ptr;

} /* namespace domahony */

#endif /* DIE2_H_ */
