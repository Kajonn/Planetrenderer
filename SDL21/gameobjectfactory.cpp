/*
 * gameobjectfactory.cpp
 *
 *  Created on: 21 apr 2013
 *      Author: Jonas
 */

#include "gameobjectfactory.hpp"
#include "Planet.h"

using namespace basegame;

GameObjectFactory::GameObjectFactory() {

}

GameObjectFactory::~GameObjectFactory() {

}

std::shared_ptr<Mesh> GameObjectFactory::createColorMesh(SDL_Surface * image_) {
   SDL_LockSurface(image_);
   int width = image_->w;
   int height = image_->h;
   glm::vec4 color;
   MeshPtr mesh(new Mesh());

//   std::vector<glm::vec4> colors[width * height];
   //std::vector<int> field[width * height]; //the int is neighbours.

//   int state = 0;
//   int ind = 0;
   for (int h = 0; h < height; ++h) {
      for (int w = 0; w < width; ++w) {
         //colors[(w * width) + h] = getPixel(*image_, w, h);
         color = getPixel(*image_, w, h);
         if (color.a > 0) {
            addBlock(*mesh, glm::vec3( w, h, 0), color);
//            field[ (w*width) + h ] = 0;
//            //Check neighbours, add to this for each neighbour
//
//            int size = 0;

            //new row
//            while (w < width && color[3] > 0) {
//               w++;
//               color = getPixel(*image_, w, h);
//               if (color[3] > 0) {
//                  //Add this point to the row
////                  field[(w*width) + h] = rectangleSizes.size()-1;
//
//               }
//            }
         }
      }
   }

   //Go trough all points per row. Find neighbours with 8, search for every connecting 8. These are complete rectangles.


   SDL_UnlockSurface(image_);
   return mesh;
}

//helper to retrive a pixel
glm::vec4
GameObjectFactory::getPixel(SDL_Surface &image_, int xcoord, int ycoord) {
   int width = image_.w;
   int height = image_.h;
   int ind = (xcoord*width) + ycoord;
   assert(ind < height*width);

   Uint32 temp, pixel;
   Uint8 red, green, blue, alpha;
   SDL_PixelFormat *fmt = image_.format;
   pixel = ( ((Uint32*)image_.pixels)[ind] );

   /* Get Red component */
   temp=pixel&fmt->Rmask; /* Isolate red component */
   temp=temp>>fmt->Rshift;/* Shift it down to 8-bit */
   temp=temp<<fmt->Rloss; /* Expand to a full 8-bit number */
   red=(Uint8)temp;

   /* Get Green component */
   temp=pixel&fmt->Gmask; /* Isolate green component */
   temp=temp>>fmt->Gshift;/* Shift it down to 8-bit */
   temp=temp<<fmt->Gloss; /* Expand to a full 8-bit number */
   green=(Uint8)temp;

   /* Get Blue component */
   temp=pixel&fmt->Bmask; /* Isolate blue component */
   temp=temp>>fmt->Bshift;/* Shift it down to 8-bit */
   temp=temp<<fmt->Bloss; /* Expand to a full 8-bit number */
   blue=(Uint8)temp;

   /* Get Alpha component */
   temp=pixel&fmt->Amask; /* Isolate alpha component */
   temp=temp>>fmt->Ashift;/* Shift it down to 8-bit */
   temp=temp<<fmt->Aloss; /* Expand to a full 8-bit number */
   alpha=(Uint8)temp;

   return glm::vec4( (float)red/256.0f, (float)green/256.0f, (float)blue/256.0f, (float)alpha/256.0f );
}

void GameObjectFactory::addBlock(Mesh &mesh_, const glm::vec3 &origin_,const glm::vec4 &color_) {
   mesh_.beginNewMesh(8, 6*3*2, color_);

   //   static GLfloat v0[] = { -1.0f, -1.0f, 1.0f };
   mesh_.addVertex(-0.5f + origin_[0], -0.5f + origin_[1], 0.5f + origin_[2], 0,0,1.0f);
   //   static GLfloat v1[] = { 0.5f, -0.5f, 0.5f };
   mesh_.addVertex( 0.5f + origin_[0], -0.5f + origin_[1], 0.5f + origin_[2], 0,0,1.0f);
   //   static GLfloat v2[] = { 0.5f, 0.5f, 0.5f };
   mesh_.addVertex(0.5f + origin_[0], 0.5f + origin_[1], 0.5f + origin_[2], 0,0,1.0f);
   //   static GLfloat v3[] = { -0.5f, 0.5f, 0.5f };
   mesh_.addVertex(-0.5f + origin_[0], 0.5f + origin_[1], 0.5f + origin_[2], 0,0,1.0f);
   //   static GLfloat v4[] = { -0.5f, -0.5f, -0.5f };
   mesh_.addVertex(-0.5f + origin_[0], -0.5f + origin_[1], -0.5f + origin_[2], 0,0,-1.0f);
   //   static GLfloat v5[] = { 0.5f, -0.5f, -0.5f };
   mesh_.addVertex(0.5f + origin_[0], -0.5f + origin_[1], -0.5f + origin_[2], 0,0,-1.0f);
   //   static GLfloat v6[] = { 0.5f, 0.5f, -0.5f };
   mesh_.addVertex(0.5f + origin_[0], 0.5f + origin_[1], -0.5f + origin_[2], 0,0,-1.0f);
   //   static GLfloat v7[] = { -0.5f, 0.5f, -0.5f };
   mesh_.addVertex(-0.5f + origin_[0], 0.5f + origin_[1], -0.5f + origin_[2], 0,0,-1.0f);

   //   glColor4ubv(red);
   //   glVertex3fv(v0);
   mesh_.addIndex(0);
   //   glColor4ubv(green);
   //   glVertex3fv(v1);
   mesh_.addIndex(1);
   //   glColor4ubv(blue);
   //   glVertex3fv(v2);
   mesh_.addIndex(2);

   //   glColor4ubv(red);
   //   glVertex3fv(v0);
   mesh_.addIndex(0);
   //   glColor4ubv(blue);
   //   glVertex3fv(v2);
   mesh_.addIndex(2);
   //   glColor4ubv(white);
   //   glVertex3fv(v3);
   mesh_.addIndex(3);

   //   glColor4ubv(green);
   //   glVertex3fv(v1);
   mesh_.addIndex(1);
   //   glColor4ubv(black);
   //   glVertex3fv(v5);
   mesh_.addIndex(5);
   //   glColor4ubv(orange);
   //   glVertex3fv(v6);
   mesh_.addIndex(6);

   //   glColor4ubv(green);
   //   glVertex3fv(v1);
   mesh_.addIndex(1);
   //   glColor4ubv(orange);
   //   glVertex3fv(v6);
   mesh_.addIndex(6);
   //   glColor4ubv(blue);
   //   glVertex3fv(v2);
   mesh_.addIndex(2);

   //   glColor4ubv(black);
   //   glVertex3fv(v5);
   mesh_.addIndex(5);
   //   glColor4ubv(yellow);
   //   glVertex3fv(v4);
   mesh_.addIndex(4);
   //   glColor4ubv(purple);
   //   glVertex3fv(v7);
   mesh_.addIndex(7);

   //   glColor4ubv(black);
   //   glVertex3fv(v5);
   mesh_.addIndex(5);
   //   glColor4ubv(purple);
   //   glVertex3fv(v7);
   mesh_.addIndex(7);
   //   glColor4ubv(orange);
   //   glVertex3fv(v6);
   mesh_.addIndex(6);

   //   glColor4ubv(yellow);
   //   glVertex3fv(v4);
   mesh_.addIndex(4);
   //   glColor4ubv(red);
   //   glVertex3fv(v0);
   mesh_.addIndex(0);
   //   glColor4ubv(white);
   //   glVertex3fv(v3);
   mesh_.addIndex(3);

   //   glColor4ubv(yellow);
   //   glVertex3fv(v4);
   mesh_.addIndex(4);
   //   glColor4ubv(white);
   //   glVertex3fv(v3);
   mesh_.addIndex(3);
   //   glColor4ubv(purple);
   //   glVertex3fv(v7);
   mesh_.addIndex(7);

   //   glColor4ubv(white);
   //   glVertex3fv(v3);
   mesh_.addIndex(3);
   //   glColor4ubv(blue);
   //   glVertex3fv(v2);
   mesh_.addIndex(2);
   //   glColor4ubv(orange);
   //   glVertex3fv(v6);
   mesh_.addIndex(6);

   //   glColor4ubv(white);
   //   glVertex3fv(v3);
   mesh_.addIndex(3);
   //   glColor4ubv(orange);
   //   glVertex3fv(v6);
   mesh_.addIndex(6);
   //   glColor4ubv(purple);
   //   glVertex3fv(v7);
   mesh_.addIndex(7);

   //   glColor4ubv(green);
   //   glVertex3fv(v1);
   mesh_.addIndex(1);
   //   glColor4ubv(red);
   //   glVertex3fv(v0);
   mesh_.addIndex(0);
   //   glColor4ubv(yellow);
   //   glVertex3fv(v4);
   mesh_.addIndex(4);

   //   glColor4ubv(green);
   //   glVertex3fv(v1);
   mesh_.addIndex(1);
   //   glColor4ubv(yellow);
   //   glVertex3fv(v4);
   mesh_.addIndex(4);
   //   glColor4ubv(black);
   //   glVertex3fv(v5);
   mesh_.addIndex(5);
}

std::shared_ptr < Mesh > GameObjectFactory::createTestMesh()
{
   std::shared_ptr<Mesh> mesh(new Mesh());

   mesh->beginNewMesh(3,3,glm::vec4(150.0,0.0,0.0,250.0));


   mesh->addVertex( -1.0f, -1.0f, 1.0f, 0,0,1.0f );
   mesh->addVertex( 1.0f, -1.0f, 1.0f, 0,0,1.0f);
   mesh->addVertex( 1.0f, 1.0f, 1.0f, 0,0,1.0f );

   mesh->addIndex(0);
   mesh->addIndex(1);
   mesh->addIndex(2);
   //addBlock(*mesh, glm::vec3(), glm::vec4());

   return mesh;
}

MeshPtr GameObjectFactory::createTestPlanetMesh(float triangleSize_) {
	Planet newPlanet;

	newPlanet.generate(30.0f, 3.0f, 30);

	return newPlanet.getMesh( triangleSize_);
}