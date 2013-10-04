/*
 * Display.h
 *
 *  Created on: 2013-09-05
 *      Author: domahony
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

namespace domahony {
namespace display {

class Display {
public:
	Display(const int& width=640, const int& height=480);
	virtual ~Display();

	const int get_width() const {
		return width;
	}

	const int get_height() const {
		return height;
	}

	SDL_Window* get_window() const {
		return window;
	}

	void resize(const int&, const int&);

private:
	SDL_Window *window;
	int width;
	int height;

};

} /* namespace display */
} /* namespace domahony */
#endif /* DISPLAY_H_ */
