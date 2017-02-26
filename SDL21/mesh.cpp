/*
 * mesh.cpp
 *
 *  Created on: 20 apr 2013
 *      Author: Jonas
 */


#include "mesh.hpp"

using namespace basegame;

Mesh::Mesh() :
      currI(0),
      currV(0),
      allocatedVertices(0),
      allocatedIndices(0) {
}

Mesh::~Mesh() {

}

void Mesh::beginNewMesh(int vertexSize, int indexSize, const glm::vec4 &color_) {
   m_indices.push_back( std::vector<unsigned int>() );
   m_indices.back().resize(indexSize);
   m_vertices.push_back( std::vector<Vertex>() );
   m_vertices.back().resize(vertexSize);
   m_colors.push_back(color_);
   allocatedVertices = vertexSize;
   allocatedIndices = indexSize;
   currV=0;
   currI=0;
}

void Mesh::addVertex(float x_, float y_, float z_, float nx_, float ny_, float nz_) {
   assert(currV<allocatedVertices);
   Vertex &v = m_vertices.back()[currV];
   v.pos[0] = x_;
   v.pos[1] = y_;
   v.pos[2] = z_;
   v.normal[0] = nx_;
   v.normal[1] = ny_;
   v.normal[2] = nz_;
   v.tex[0] = 0;
   v.tex[1] = 0;
   currV++;
}

void Mesh::addVertex(const Vertex &vertex_) {
   assert(currV<allocatedVertices);
   Vertex &v = m_vertices.back()[currV];
   v.pos[0] = vertex_.pos[0];
   v.pos[1] = vertex_.pos[1];
   v.pos[2] = vertex_.pos[2];
   currV++;
}

void Mesh::addIndex(int ind_) {
   assert(currI<allocatedIndices);
   m_indices.back()[currI] = ind_;
   currI++;
}

void Mesh::clear() {
   m_indices.clear();
   m_vertices.clear();
}





