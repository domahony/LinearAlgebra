/*
 * Die3.h
 *
 *  Created on: 2014-02-02
 *      Author: domahony
 */

#ifndef DIE3_H_
#define DIE3_H_

#include <vector>

namespace domahony {

class Die3 {
public:
	Die3();
	std::vector<float>& get_data() {
		return data;
	}

	virtual ~Die3();
private:
	std::vector<float> data;
};

} /* namespace domahony */
#endif /* DIE3_H_ */
