//============================================================================
// Name        : gameon.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <Windows.h>
#include "commonenums.hpp"
#include "SDL_image.h"
#include "gameon.hpp"
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include "mesh.hpp"
#include "gameobjectfactory.hpp"
#include "jobhandler.h"

using namespace std;
using namespace basegame;

///XXX
const int endTimeS = 60;
const int BUFFERSIZE = 200;
char buff[BUFFERSIZE];
bool test = true;
float angle = 0;

float testMeshDiff = 0.5f;
float testMesh = 1.5f;
float maxTestMesh = 7.0f;
int currentMesh = 0;
std::shared_ptr<Mesh> planetmeshes[7]; 

GLfloat light_position0[] = { 50.0f, 50.0f, -10.0f, 1.0f };

GLfloat light_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

Game::Game() :
      m_run(true),
	  m_jobHandler(4), 
	  m_camera(new Camera()) {
}

Game::~Game() {

}

void Game::printvalue(SDL_Surface* Surf_Dest, unsigned int value, int x,
      int y) {
//	if(!m_numberSurface || !Surf_Dest)
//		return;
//
//    if(sprintf ( buff, "%d",  value)<0) {
//   	 return;
//    }
//
//	int numsize = m_numberSurface->w/10;
//	int numheight = m_numberSurface->h;
//
//    int currx= x;
//    for(int i = 0; i<BUFFERSIZE && buff[i]!=0; i++) {
//		int ind = m_characterMap[buff[i]];
//
//		SDL_Rect srcrect;
//		srcrect.x = ind*numsize;
//		srcrect.y = 0;
//		srcrect.w = numsize;
//		srcrect.h = numheight;
//
//		SDL_Rect targetRect;
//		targetRect.x = currx;
//		targetRect.y = y;
//
//		SDL_BlitSurface( m_numberSurface, &srcrect, Surf_Dest, &targetRect);
//		currx+=numsize;
//    }

}

bool Game::init() {

   //Start SDL
   if (SDL_Init(SDL_INIT_EVERYTHING)) {
      /* Failed, exit. */
      fprintf(stderr, "Video initialization failed: %s\n",
      SDL_GetError( ) );
      return false;
   }

   /* Let's get some video information. */
   //info = SDL_getw( );

   //if( !info ) {
   //   /* This should probably never happen. */
   //   fprintf( stderr, "Video query failed: %s\n",
   //         SDL_GetError( ) );
   //   return false;
   //}

   // load support for the JPG and PNG image formats
            int flags=IMG_INIT_JPG|IMG_INIT_PNG;
            int initted=IMG_Init(flags);
            if( (initted&flags) != flags) {
               printf("IMG_Init: Failed to init required jpg and png support!\n");
               printf("IMG_Init: %s\n", IMG_GetError());
               // handle error
            }

            /*
             * Set our width/height to 640/480 (you would
             * of course let the user decide this in a normal
             * app). We get the bpp we will request from
             * the display. On X11, VidMode can't change
             * resolution, so this is probably being overly
             * safe. Under Win32, ChangeDisplaySettings
             * can change the bpp.
             */
            width = 640;
            height = 480;
//            bpp = info->vfmt->BitsPerPixel;

            /*
             * Now, we want to setup our requested
             * window attributes for our OpenGL window.
             * We want *at least* 5 bits of red, green
             * and blue. We also want at least a 16-bit
             * depth buffer.
             *
             * The last thing we do is request a double
             * buffered window. '1' turns on double
             * buffering, '0' turns it off.
             *
             * Note that we do not use SDL_DOUBLEBUF in
             * the flags to SDL_SetVideoMode. That does
             * not affect the GL attribute state, only
             * the standard 2D blitting setup.
             */
            SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
            SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
            SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
            SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
            SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );
            SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 8 );
            SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

            /*
             * We want to request that SDL provide us
             * with an OpenGL window, in a fullscreen
             * video mode.
             *
             * EXERCISE:
             * Make starting windowed an option, and
             * handle the resize events properly with
             * glViewport.
             */
			flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

			sdlWindow = SDL_CreateWindow("",  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags );
            /*
             * Set the video mode
             */
			 if( sdlWindow == 0 ) {
               /*
                * This could happen for a variety of reasons,
                * including DISPLAY not being set, the specified
                * resolution not being available, etc.
                */
               fprintf( stderr, "Video mode set failed: %s\n",
                     SDL_GetError( ) );
               return false;
            }

			 SDL_GLContext glContext = SDL_GL_CreateContext(sdlWindow);

            float ratio = (float) width / (float) height;

            /* Our shading model--Gouraud (smooth). */
            glShadeModel( GL_SMOOTH );

            /* Culling. */
            glCullFace( GL_BACK );
            glFrontFace( GL_CCW );
            glEnable( GL_CULL_FACE );

            glEnable( GL_LIGHTING );
            glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
            glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
            glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
            glLightfv( GL_LIGHT0, GL_POSITION, light_position0);
			

            /* Set the clear color. */
            glClearColor( 100, 100, 100, 0 );

            /* Setup our viewport. */
            glViewport( 0, 0, width, height );

			m_camera->setViewPort(width, height);

            /*
             * Change to the projection matrix and set
             * our viewing volume.
             */
            //glMatrixMode( GL_PROJECTION );
            //glLoadIdentity( );
            /*
             * EXERCISE:
             * Replace this with a call to glFrustum.
             */
            //gluPerspective( 60.0, ratio, 1.0, 1024.0 );

			m_camera->setNear(1.0f);
			m_camera->setFar(1024.0f);
			m_camera->setHFov(60.0f);

			m_camera->setPosition(glm::vec3(0 , 0, -100.0f));

            GameObjectFactory factory;
            //m_testMesh = factory.createTestMesh();

            m_imageManager.loadImage("test", "C:\\Users\\Jonas\\Documents\\Visual Studio 2012\\Projects\\SDL21\\Debug\\resources\\Red.png");
            m_testMesh = factory.createColorMesh(m_imageManager.getSurface("test"));

			for(int i = 0; i<7; i++) 
				planetmeshes[i] = factory.createTestPlanetMesh((float)i+1);
			
            return true;
         }

void Game::events(SDL_Event & event_) {
   if (event_.type == SDL_QUIT) {
      m_run = false;
   } else {

	   //Events will affect camera and scene

	  if(event_.type == SDL_MOUSEBUTTONDOWN && 
		 event_.button.button == SDL_BUTTON_LEFT) {
			 m_testMesh = planetmeshes[currentMesh];
			 currentMesh=(currentMesh+1)%7;
	  } else 
	  if(event_.type == SDL_MOUSEMOTION) {		  
		  m_camera->addViewRotation((float)event_.motion.xrel, (float)event_.motion.yrel, 0);
	  } else if(event_.type == SDL_KEYDOWN) {
		
		  if(event_.key.keysym.sym == SDLK_UP) {
			  m_camera->translateInLookAt(1.0f);
		  } else if(event_.key.keysym.sym == SDLK_DOWN) {
			  m_camera->translateInLookAt(-1.0f);
		  }
	  
	  }
   }
}

void Game::update() {
	test++;
}

void Game::render() {
   /* Clear the color and depth buffers. */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glLoadMatrixf(glm::value_ptr(m_camera->getProjectionMatrix()));

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glLoadMatrixf(glm::value_ptr(m_camera->getViewMatrix()));
   
   if(test) {
      angle++;
   }

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);
   glRotatef(angle, 0 , 1.0f  , 0);

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_INDEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);

   for (int i = 0; i < m_testMesh->getNBuffers(); ++i) {
      glColor4fv( glm::value_ptr( m_testMesh->getColor(i) ) );
	  glVertexPointer(3, GL_FLOAT, sizeof(float)*8, m_testMesh->getVertices(i));
	  glNormalPointer(GL_FLOAT, sizeof(float)*8, m_testMesh->getNormals(i));
      int nind = m_testMesh->getNTriangles(i)*3;
	  glDrawElements(GL_TRIANGLES, nind, GL_UNSIGNED_INT, m_testMesh->getIndices(i));
   }

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_INDEX_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);

   GLenum error = glGetError();
   if(error) {
      std::cerr << error << std::endl;
   }

   
   //testCube();

   /*
    * Swap the buffers. This this tells the driver to
    * render the next frame from the contents of the
    * back-buffer, and to set all rendering operations
    * to occur on what was the front-buffer.
    *
    * Double buffering prevents nasty visual tearing
    * from the application drawing on areas of the
    * screen that are being updated at the same time.
    */
   SDL_GL_SwapWindow(sdlWindow);
}


void Game::testCube() {

   static GLfloat v0[] = { -1.0f, -1.0f, 1.0f };
   static GLfloat v1[] = { 1.0f, -1.0f, 1.0f };
   static GLfloat v2[] = { 1.0f, 1.0f, 1.0f };
   static GLfloat v3[] = { -1.0f, 1.0f, 1.0f };
   static GLfloat v4[] = { -1.0f, -1.0f, -1.0f };
   static GLfloat v5[] = { 1.0f, -1.0f, -1.0f };
   static GLfloat v6[] = { 1.0f, 1.0f, -1.0f };
   static GLfloat v7[] = { -1.0f, 1.0f, -1.0f };
   static GLubyte red[] = { 255, 0, 0, 255 };
   static GLubyte green[] = { 0, 255, 0, 255 };
   static GLubyte blue[] = { 0, 0, 255, 255 };
   static GLubyte white[] = { 255, 255, 255, 255 };
   static GLubyte yellow[] = { 0, 255, 255, 255 };
   static GLubyte black[] = { 0, 0, 0, 255 };
   static GLubyte orange[] = { 255, 255, 0, 255 };
   static GLubyte purple[] = { 255, 0, 255, 0 };

   /* Send our triangle data to the pipeline. */
   glBegin(GL_TRIANGLES);

   glColor4ubv(red);
   glVertex3fv(v0);
   glColor4ubv(green);
   glVertex3fv(v1);
   glColor4ubv(blue);
   glVertex3fv(v2);

   glColor4ubv(red);
   glVertex3fv(v0);
   glColor4ubv(blue);
   glVertex3fv(v2);
   glColor4ubv(white);
   glVertex3fv(v3);

   glColor4ubv(green);
   glVertex3fv(v1);
   glColor4ubv(black);
   glVertex3fv(v5);
   glColor4ubv(orange);
   glVertex3fv(v6);

   glColor4ubv(green);
   glVertex3fv(v1);
   glColor4ubv(orange);
   glVertex3fv(v6);
   glColor4ubv(blue);
   glVertex3fv(v2);

   glColor4ubv(black);
   glVertex3fv(v5);
   glColor4ubv(yellow);
   glVertex3fv(v4);
   glColor4ubv(purple);
   glVertex3fv(v7);

   glColor4ubv(black);
   glVertex3fv(v5);
   glColor4ubv(purple);
   glVertex3fv(v7);
   glColor4ubv(orange);
   glVertex3fv(v6);

   glColor4ubv(yellow);
   glVertex3fv(v4);
   glColor4ubv(red);
   glVertex3fv(v0);
   glColor4ubv(white);
   glVertex3fv(v3);

   glColor4ubv(yellow);
   glVertex3fv(v4);
   glColor4ubv(white);
   glVertex3fv(v3);
   glColor4ubv(purple);
   glVertex3fv(v7);

   glColor4ubv(white);
   glVertex3fv(v3);
   glColor4ubv(blue);
   glVertex3fv(v2);
   glColor4ubv(orange);
   glVertex3fv(v6);

   glColor4ubv(white);
   glVertex3fv(v3);
   glColor4ubv(orange);
   glVertex3fv(v6);
   glColor4ubv(purple);
   glVertex3fv(v7);

   glColor4ubv(green);
   glVertex3fv(v1);
   glColor4ubv(red);
   glVertex3fv(v0);
   glColor4ubv(yellow);
   glVertex3fv(v4);

   glColor4ubv(green);
   glVertex3fv(v1);
   glColor4ubv(yellow);
   glVertex3fv(v4);
   glColor4ubv(black);
   glVertex3fv(v5);

   glEnd();

}

void Game::execute() {

   SDL_Event event;

   while (m_run) {
      while (SDL_PollEvent(&event)) {
         events(event);
      }

      update();

      render();
	  //TODO set target fps
      SDL_Delay(30);
   }

}

void Game::cleanup() {

   IMG_Quit();
   //Quit SDL
   SDL_Quit();
}

