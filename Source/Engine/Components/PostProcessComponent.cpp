#include "PostProcessComponent.h"


namespace neu {
	FACTORY_REGISTER(PostProcessComponent)

	void PostProcessComponent::Update(float dt)	{
	}

	void PostProcessComponent::Apply(Program& program) {
		program.SetUniform("u_parameters", (uint32_t)parameters);
		program.SetUniform("u_colorTint", colorTint);

		program.SetUniform("u_blend", blend);
		program.SetUniform("u_vignetteRadius", vignetteRadius);
		program.SetUniform("u_vignetteSoftness", vignetteSoftness);
	}

	void PostProcessComponent::Read(const serial_data_t& value) {
		Object::Read(value);
	}

	void PostProcessComponent::UpdateGui() {
		uint32_t iparameters = (uint32_t)parameters;

		// Gray Scale
		bool parameter = (iparameters & (uint32_t)Parameters::GrayScale) != 0u;
		if (ImGui::Checkbox("Gray Scale", &parameter)) {
			if (parameter) iparameters |= (uint32_t)Parameters::GrayScale;
			else iparameters &= ~(uint32_t)Parameters::GrayScale;
		}

		// Color Tint
		parameter = (iparameters & (uint32_t)Parameters::ColorTint) != 0u;
		if (ImGui::Checkbox("Color Tint", &parameter)) {
			if (parameter) iparameters |= (uint32_t)Parameters::ColorTint;
			else iparameters &= ~(uint32_t)Parameters::ColorTint;
		}

		// Scanline
		parameter = (iparameters & (uint32_t)Parameters::Scanline) != 0u;
		if (ImGui::Checkbox("Scanline", &parameter)) {
			if (parameter) iparameters |= (uint32_t)Parameters::Scanline;
			else iparameters &= ~(uint32_t)Parameters::Scanline;
		}

		// Grain
		parameter = (iparameters & (uint32_t)Parameters::Grain) != 0u;
		if (ImGui::Checkbox("Grain", &parameter)) {
			if (parameter) iparameters |= (uint32_t)Parameters::Grain;
			else iparameters &= ~(uint32_t)Parameters::Grain;
		}

		// Invert
		parameter = (iparameters & (uint32_t)Parameters::Invert) != 0u;
		if (ImGui::Checkbox("Invert Colors", &parameter)) {
			if (parameter) iparameters |= (uint32_t)Parameters::Invert;
			else iparameters &= ~(uint32_t)Parameters::Invert;
		}

		// Vignette (custom)
		parameter = (iparameters & (uint32_t)Parameters::Vignette) != 0u;
		if (ImGui::Checkbox("Vignette", &parameter)) {
			if (parameter) iparameters |= (uint32_t)Parameters::Vignette;
			else iparameters &= ~(uint32_t)Parameters::Vignette;
		}

		parameters = (Parameters)iparameters;

		// Controls for values
		// Color edit for tint
		ImGui::ColorEdit3("Color Tint (RGB)", glm::value_ptr(colorTint));

		// Blend slider 0-1
		ImGui::SliderFloat("Blend", &blend, 0.0f, 1.0f);

		// Vignette controls
		ImGui::SliderFloat("Vignette Radius", &vignetteRadius, 0.0f, 1.5f, "%.2f");
		ImGui::SliderFloat("Vignette Softness", &vignetteSoftness, 0.0f, 1.0f, "%.2f");

	}
}
