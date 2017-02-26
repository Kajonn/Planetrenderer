/*
 * imagemanager.hpp
 *
 *  Created on: 3 dec 2012
 *      Author: Jonas
 */

#ifndef IMAGEMANAGER_HPP_
#define IMAGEMANAGER_HPP_

#include "SDL.h"
#include <map>
#include <string>

namespace basegame {

	//Resource manager for images
	class ImageManager {

	public:

		ImageManager();
		~ImageManager();

		/**
		 * Load an image from the provided filepath and set it as a specific tag
		 */
		bool loadImage(const std::string &tag_, const char *file);

		/**
		 * Get the image for a jewel type
		 */
		SDL_Surface * getSurface(const std::string &tag_) const;

	private:

		typedef std::map<std::string, SDL_Surface*> ImageMap;
		ImageMap m_loadedImages;

	};


}


#endif /* IMAGEMANAGER_HPP_ */
