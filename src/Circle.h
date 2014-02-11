/*
 * Circle.h
 *
 *  Created on: 2014-02-09
 *      Author: domahony
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include <vector>

namespace domahony {

class Circle {
public:
	Circle();
	virtual ~Circle();
	std::vector<float>& get_data() {
		return data;
	}

private:
	std::vector<float> data;
};

} /* namespace domahony */
#endif /* CIRCLE_H_ */
