#include "Material.h"
#include "Program.h"

namespace neu {

	bool Material::Load(const std::string& filename) {
		neu::serial::document_t document;
		if (!neu::serial::Load(filename, document)) {
			LOG_ERROR("Could not load Material json {}", filename);
			return false;
		}
		std::string programName;
		SERIAL_READ_NAME(document, "program", programName);

		program = Resources().Get<Program>(programName);

		std::string textureName;
		SERIAL_READ_NAME(document, "texture", textureName);

		texture = Resources().Get<Texture>(programName);

		SERIAL_READ(document, shininess);
		SERIAL_READ(document, tiling);
		SERIAL_READ(document, offset);

		return true;
	}

	void Material::Bind() {
		program->Use();
		
		program->Link();

		program->SetUniform("u_material.shininess", shininess);
		program->SetUniform("u_material.tiling", tiling);
		program->SetUniform("u_material.offset", offset);
	}
}