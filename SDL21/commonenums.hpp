/*
 * commonenums.hpp
 *
 *  Created on: 5 dec 2012
 *      Author: Jonas
 */

#ifndef COMMONENUMS_HPP_
#define COMMONENUMS_HPP_

#include <assert.h>
#include <iostream>

namespace basegame {
	static const float PI_APROX = 3.14159265359f;
	static const float PI2_APROX = 9.86960440109f;
};

#ifdef GAME_DEBUG
#define DEBUGPRINT(s) std::cerr << s << std::endl
#else
#define DEBUGPRINT(s)
#endif

#endif /* COMMONENUMS_HPP_ */
