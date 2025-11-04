int main(int argc, char* argv[]) {
    neu::file::SetCurrentDirectory("Assets");
    LOG_INFO("current directory {}", neu::file::GetCurrentDirectory());

    // Initialize engine
    LOG_INFO("initialize engine...");
    neu::GetEngine().Initialize();

    SDL_Event e;
    bool quit = false;

	//scene
    auto scene = std::make_unique<neu::Scene>();
    scene->Load("scenes/scene02.json");
	scene->Start();

	auto editor = std::make_shared<neu::Editor>();

    // === MAIN LOOP ===
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
			ImGui_ImplSDL3_ProcessEvent(&e);
        }

        neu::GetEngine().Update();
		float dt = neu::GetEngine().GetTime().GetDeltaTime();

        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

		scene->Update(dt);

		editor->Begin();
		editor->UpdateGui(*scene);
       
        neu::GetEngine().GetRenderer().Clear();
      
		scene->Draw(neu::GetEngine().GetRenderer());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        neu::GetEngine().GetRenderer().Present();
    }

    neu::GetEngine().Shutdown();

    return 0;
}
