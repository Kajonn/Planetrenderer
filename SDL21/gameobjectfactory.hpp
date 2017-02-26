/*
 * gameobjectfactory.hpp
 *
 *  Created on: 20 apr 2013
 *      Author: Jonas
 */

#ifndef GAMEOBJECTFACTORY_HPP_
#define GAMEOBJECTFACTORY_HPP_

#include "SDL.h"
#include "mesh.hpp"
#include <glm.hpp>

namespace basegame {

   class GameObjectFactory {

   public:

      GameObjectFactory();

      ~GameObjectFactory();

      static MeshPtr createColorMesh(SDL_Surface * image_);

      static MeshPtr createTestMesh();

	  static MeshPtr createTestPlanetMesh(float triangleSize_);

   private:

      static void addBlock(Mesh &mesh_, const glm::vec3 &origin_,const glm::vec4 &color_);

      static glm::vec4 getPixel(SDL_Surface &image_, int xcoord, int ycoord);


   };

}



#endif /* GAMEOBJECTFACTORY_HPP_ */
