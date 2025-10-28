  
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

		//texture
		std::string textureName;
		SERIAL_READ_NAME(document, "texture", textureName);
		baseMap = Resources().Get<Texture>(programName);

		textureName = "";
		SERIAL_READ_NAME(document, "specularMap", textureName);
		if(!textureName.empty()) specularMap = Resources().Get<Texture>(textureName);

		SERIAL_READ(document, baseColor);
		SERIAL_READ(document, shininess);
		SERIAL_READ(document, tiling);
		SERIAL_READ(document, offset);

		return true;
	}

	void Material::Bind() {
		program->Use();
		if (baseMap) {
			baseMap->SetActive(GL_TEXTURE0);
			baseMap->Bind();
		}

		if (specularMap) {
			specularMap->SetActive(GL_TEXTURE0);
			specularMap->Bind();
		}

		program->SetUniform("u_material.baseColor", baseColor);
		program->SetUniform("u_material.shininess", shininess);
		program->SetUniform("u_material.tiling", tiling);
		program->SetUniform("u_material.offset", offset);
	}

	void Material::UpdateGui() {
		if (!ImGui::CollapsingHeader("Material",ImGuiTreeNodeFlags_DefaultOpen)) {
			/*ImGui::Text("Name: %s", name.c_str());
			ImGui::Text("Shader: %s", program->name.c_str());
			if(baseMap)
				ImGui::Text("Base Map: %s", baseMap->name.c_str());
			else
				ImGui::Text("Base Map: None");*/
			ImGui::ColorEdit3("Base Color", &baseColor[0]);
			ImGui::DragFloat("Shininess", &shininess, 1.0f);
			ImGui::DragFloat2("Tiling", glm::value_ptr(tiling), 0.1f);
			ImGui::DragFloat2("Offset", glm::value_ptr(offset), 0.1f);
		}
	}
}