/*
 * mesh.hpp
 *
 *  Created on: 20 apr 2013
 *      Author: Jonas
 */

#ifndef MESH_HPP_
#define MESH_HPP_

#include "commonenums.hpp"
#include <glm.hpp>
#include <vector>
#include <memory>

namespace basegame {

   struct Vertex {
      float pos[3];    //World coord
      float normal[3]; //Normal coord
      float tex[2];    //Texture coord
   };

   //Holds vertices and indices
   //TODO template depending on vertex size
   class Mesh {


   public:
      Mesh();

      ~Mesh();

      void beginNewMesh(int vertexSize, int indexSize, const glm::vec4 &color_); 

	  void addVertex(float x_, float y_, float z_, float nx_, float ny_, float nz_);

      void addVertex(const Vertex &vertex_);

      void addIndex(int i);

      inline int getNBuffers();

      inline int getNTriangles(int ind_);

      inline void *getIndices(int id); //

      inline void *getVertices(int id); //

	  inline void *getNormals(int id); //

      inline const glm::vec4 &getColor(int id); //

      void clear();
   private:

      std::vector< glm::vec4 > m_colors;

      std::vector< std::vector<unsigned int> > m_indices;

        //TODO this should be vertex type not vec3
      std::vector< std::vector<Vertex> > m_vertices;

      int currI;
      int currV;
      int allocatedVertices;
      int allocatedIndices;


   };
   typedef std::shared_ptr<Mesh> MeshPtr;

   inline int Mesh::getNBuffers() {
      return m_indices.size();
   }

   inline int Mesh::getNTriangles(int ind_) {
      return (m_indices[ind_]).size()/3;
   }

   inline void * Mesh::getIndices(int ind_) {
      return &((m_indices[ind_])[0]);
   }

   inline void * Mesh::getVertices(int ind_) {
      return &((m_vertices[ind_])[0]);
   }

   inline void * Mesh::getNormals(int ind_) {
	   return &((m_vertices[ind_])[0].normal);
   }

   inline const glm::vec4 & Mesh::getColor(int id) {
      return m_colors[id];
   }

}


#endif /* MESH_HPP_ */
