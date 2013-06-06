/*
 * Test.h
 *
 *  Created on: 2013-06-04
 *      Author: domahony
 */

#ifndef TEST_H_
#define TEST_H_

#include <SDL.h>
#include "App.h"

namespace domahony {
namespace test {

class Test: public domahony::sdl::App {
public:
	Test();
	virtual ~Test();

protected:
	int _init();
	int _display();

};

} /* namespace test */
} /* namespace domahony */
#endif /* TEST_H_ */
