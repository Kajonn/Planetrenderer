/*
 * imagemanager.cpp
 *
 *  Created on: 3 dec 2012
 *      Author: Jonas
 */

#include "SDL.h"
#include "SDL_image.h"
#include "imagemanager.hpp"

using namespace basegame;

ImageManager::ImageManager() {

}

ImageManager::~ImageManager() {
	for (ImageMap::iterator it = m_loadedImages.begin();
			it != m_loadedImages.end(); ++it) {
	    SDL_FreeSurface(it->second);
	}
}

bool ImageManager::loadImage(const std::string &tag_, const char * file) {
    SDL_Surface * surface = IMG_Load(file);
    if(!surface)
    	return false;

	m_loadedImages[tag_] = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
    SDL_FreeSurface(surface);
    return true;
}

SDL_Surface * ImageManager::getSurface(const std::string &tag_) const {
	if(!m_loadedImages.count(tag_))
		return NULL;
	else
		return m_loadedImages.find(tag_)->second;
}
