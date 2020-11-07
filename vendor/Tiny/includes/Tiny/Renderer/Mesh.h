#pragma once

#include <vector>

#include "glm/glm.hpp"

namespace Tiny {

	/*struct Vertex {
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec3 color;
		glm::vec2 texCoords;
	};*/

	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		bool loadOBJ(
			const char* path,
			std::vector < glm::vec3 >& out_vertices,
			std::vector < glm::vec2 >& out_uvs,
			std::vector < glm::vec3 >& out_normals
		);

	private:
		//std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		//TEMPORARY
		std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
		std::vector< glm::vec3 > temp_vertices;
		std::vector< glm::vec2 > temp_uvs;
		std::vector< glm::vec3 > temp_normals;
	};
}


