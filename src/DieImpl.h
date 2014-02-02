/*
 * DieImpl.h
 *
 *  Created on: 2014-01-27
 *      Author: domahony
 */

#ifndef DIEIMPL_H_
#define DIEIMPL_H_

namespace domahony {

class DieImpl {
public:
	DieImpl();
	void render() const;

	virtual ~DieImpl();

private:
	domahony::opengl::Program program;
};

} /* namespace domahony */
#endif /* DIEIMPL_H_ */
