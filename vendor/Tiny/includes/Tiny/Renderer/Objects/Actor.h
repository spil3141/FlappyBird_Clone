#pragma once

#include "glm/glm.hpp"

namespace Tiny {

	struct Vertex {
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec3 color;
		glm::vec2 texCoords;
	};

	class Actor
	{
	public:
		Actor();
		~Actor();

		inline virtual glm::mat4& GetTransform() { return m_ActorData.Transform; }

		void SetVertices(std::vector<Vertex> vertices);
		const unsigned int& GetVertexCount() const;

		const unsigned int& GetVAO() const;

	private:

		struct ActorData {
			glm::mat4 Transform;
			unsigned int VertexCount;
			unsigned int VertexArrayObjID;
			unsigned int VertexBufferObjID;
		};

		ActorData m_ActorData;
	};
}


