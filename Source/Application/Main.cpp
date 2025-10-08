
int main(int argc, char* argv[]) {
    neu::file::SetCurrentDirectory("Assets");
    LOG_INFO("current directory {}", neu::file::GetCurrentDirectory());

    // initialize engine
    LOG_INFO("initialize engine...");
    neu::GetEngine().Initialize();

    // initialize scene


    SDL_Event e;
    bool quit = false;

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // update
        neu::GetEngine().Update();

        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

		float angle = neu::GetEngine().GetTime().GetTime() * 90.0f;
		float scale = neu::math::Remap(-1.0f, 1.0f, 0.3f, 1.5f, neu::math::sin(neu::GetEngine().GetTime().GetTime() * 2.0f));

		neu::vec2 mouse = neu::GetEngine().GetInput().GetMousePosition();
		neu::vec2 position;
		position.x = neu::math::Remap(0.0f, (float)neu::GetEngine().GetRenderer().GetWidth(), -1.0f, 1.0f, mouse.x);
		position.y = -neu::math::Remap(0.0f, (float)neu::GetEngine().GetRenderer().GetWidth(), -1.0f, 1.0f, mouse.y);
      

        // draw
        neu::vec3 color{ 0, 0, 0 };
        neu::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        neu::GetEngine().GetRenderer().Clear();

        glBegin(GL_TRIANGLES);


        glColor3f(0, 0, 1);
        glVertex3f(-0.5f, 0.5f, 0);
        glColor3f(0, 1, 0);
        glVertex3f(0.5f, 0.7f, 0);
        glColor3f(1, 0, 0);
        glVertex3f(0.7f, -0.5f, 0);

        glEnd();

        //glLoadIdentity();
		//glPushMatrix();

        

        neu::GetEngine().GetRenderer().Present();
    }

    neu::GetEngine().Shutdown();

    return 0;
}


