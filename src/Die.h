/*
 * Die.h
 *
 *  Created on: 2014-01-26
 *      Author: domahony
 */

#ifndef DIE_H_
#define DIE_H_

#include "Body2.h"
#include <boost/shared_ptr.hpp>

namespace domahony {

class DieImpl;

class Die: public domahony::Body2 {
public:
	Die();
	virtual ~Die();

	void render() const;
private:
	boost::shared_ptr<DieImpl> impl;

};

typedef boost::shared_ptr<Die> DiePtr;

} /* namespace domahony */
#endif /* DIE_H_ */
