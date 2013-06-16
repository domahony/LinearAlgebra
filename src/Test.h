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
	Test(const int& width=640, const int& height=480);
	virtual ~Test();

protected:
	int _init();
	int _display();

private:
	int width;
	int height;

};

} /* namespace test */
} /* namespace domahony */
#endif /* TEST_H_ */
