/*
 * gameon.hpp
 *
 *  Created on: 17 apr 2013
 *      Author: Jonas
 */

#ifndef GAMEON_HPP_
#define GAMEON_HPP_

#include "SDL.h"
#include <memory>
#include "imagemanager.hpp"
#include "mesh.hpp"
#include "jobhandler.h"
#include "camera.h"

namespace basegame {

	/**
	 * Main game class. Runs update and render logic and handles event.
	 */
	class Game {

	public:
		/**
		 * Constructor
		 */
		Game();
		~Game();

		/**
		 * Init stuff
		 */
		bool init();

		/**
		 * Handle events
		 */
		void events(SDL_Event & event_);

		/**
		 * Udpate the playingfield
		 */
		void update();

		/**
		 * Renders
		 */
		void render();

		/**
		 * The game main function.
		 */
		void execute();

		/**
		 * Cleanups all allocated things before quitting SDL.
		 */
		void cleanup();

	private:

		void testCube();

		/* Information about the current video settings. */
		//const SDL_VideoInfo* info;
		/* The window used by the game */
		SDL_Window* sdlWindow;
		/* Dimensions of our window. */
		int width;
		int height;
		/* Color depth in bits of our window. */
		int bpp;
		/* Flags we will pass into SDL_SetVideoMode. */
		int flags;


		//Render the value using the numberSurface
		void printvalue(SDL_Surface* Surf_Dest, unsigned int value, int x, int y);

		//True while the game is running
		bool m_run;

		MeshPtr m_testMesh;

        ImageManager m_imageManager;

		Jobhandler m_jobHandler;

		CameraPtr m_camera;

	};




}

#endif /* GAMEON_HPP_ */
