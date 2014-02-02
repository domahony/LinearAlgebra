/*
 * Die.cc
 *
 *  Created on: 2014-01-26
 *      Author: domahony
 */

#include "Die.h"
#include "DieImpl.h"

namespace domahony {

Die::Die() : impl(new DieImpl()) {
	// TODO Auto-generated constructor stub

}

Die::~Die() {
	// TODO Auto-generated destructor stub
}

void Die::render() const {
	impl->render();
}

} /* namespace domahony */
