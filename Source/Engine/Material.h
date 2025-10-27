#pragma once
#include "Resources/Resource.h"

namespace neu {
	class Shader;
	class Program;

	class Material : public Resource {
	private:
		bool Load(const std::string& filename);
		void Bind();

	public:
		float shininess{ 2 };
		glm::vec2 tiling{ 1,1 };
		glm::vec2 offset{ 0,0 };

		res_t<Program> program;
		res_t<Texture> texture;

	};
}