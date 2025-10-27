int main(int argc, char* argv[]) {
    neu::file::SetCurrentDirectory("Assets");
    LOG_INFO("current directory {}", neu::file::GetCurrentDirectory());

    // Initialize engine
    LOG_INFO("initialize engine...");
    neu::GetEngine().Initialize();

    SDL_Event e;
    bool quit = false;

    // === OPENGL INIT ===
    std::vector<neu::vec3> points = {
    { 0.0f,  0.5f, 0.0f },  
    { 0.118f,  0.154f, 0.0f },
    { 0.475f,  0.154f, 0.0f },
    { 0.191f, -0.059f, 0.0f },
    { 0.293f, -0.404f, 0.0f },
    { 0.0f,  -0.191f, 0.0f },
    { -0.293f, -0.404f, 0.0f },
    { -0.191f, -0.059f, 0.0f },
    { -0.475f,  0.154f, 0.0f },
    { -0.118f,  0.154f, 0.0f }
    };

    std::vector<neu::vec3> colors = {
     {1, 0, 0},  
     {1, 0.5, 0}, 
     {1, 1, 0},   
     {0, 1, 0},   
     {0, 1, 1},   
     {0, 0, 1},   
     {0.5, 0, 1},
     {1, 0, 1},   
     {1, 0, 0.5}, 
     {1, 0, 0}    
    };

    std::vector<neu::vec2> texcoord{ {0,0},{0.5f,1.0f},{1,1} };

    struct Vertex
    {
		neu::vec3 position;
		neu::vec3 color;
		neu::vec2 texcoord;
    };

    std::vector<Vertex> vertices{
    {{-0.5f, -0.5f, 0.0f}, {1, 0, 0}, {0, 0}},   // bottom left
    {{ 0.5f, -0.5f, 0.0f}, {0, 1, 0}, {1, 0}},   // bottom right
    {{ 0.5f,  0.5f, 0.0f}, {0, 0, 1}, {1, 1}},   // top right
    {{-0.5f,  0.5f, 0.0f}, {1, 1, 0}, {0, 1}}    // top left
    };

    std::vector<GLuint> indices{
    0, 1, 2,
    2, 3, 0
    };


	//Vertex Buffer Object
	neu::res_t<neu::VertexBuffer> vb = std::make_shared<neu::VertexBuffer>();

	vb->CreateVertexBuffer((GLsizei)sizeof(Vertex) * (GLsizei)vertices.size(), (GLsizei)vertices.size(), vertices.data());
	vb->CreateIndexBuffer(GL_UNSIGNED_INT, (GLsizei)indices.size(), indices.data());
	vb->SetAttribute(0, 3, sizeof(Vertex), offsetof(Vertex, position));
	vb->SetAttribute(1, 3, sizeof(Vertex), offsetof(Vertex, color));
	vb->SetAttribute(2, 2, sizeof(Vertex), offsetof(Vertex, texcoord));

    // Create shaders using the new Shader class
    /*auto vs = std::make_shared<neu::Shader>();
    vs->Load("shaders/basic.lit.vert", GL_VERTEX_SHADER);

    auto fs = std::make_shared<neu::Shader>();
    fs->Load("shaders/basic.lit.frag", GL_FRAGMENT_SHADER);*/

    //transform
	float rotation = 0.0f;
	glm::vec3 eye = { 0, 0, 5 };

	neu::Transform transform{ {0,0,0} };
	neu::Transform cameraTransform{ {0,0,3} };

	auto material = neu::Resources().Get<neu::Material>("materials/spot.mat");
	material->Bind();

	auto program = neu::Resources().Get<neu::Program>("shaders/basic_lit.prog");
    program->Use();
    
    
    //textures
    neu::res_t<neu::Texture> texture = neu::Resources().Get<neu::Texture>("textures/spot_diffuse.png");

	//set light uniforms
	program->SetUniform("u_light.color", glm::vec3(0.5f));
	program->SetUniform("u_ambient_light", glm::vec3(0.2f));
	neu::Transform lightTransform{ {2,4,3} };

	//projection matrix
	float aspect = (float)neu::GetEngine().GetRenderer().GetWidth() / (float)neu::GetEngine().GetRenderer().GetHeight();
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect, 0.01f , 100.0f);
	program->SetUniform("u_projection", projection);

	auto model3d = std::make_shared<neu::Model>();
    model3d->Load("models/spot.obj");


    // === MAIN LOOP ===
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
        }

        neu::GetEngine().Update();
		float dt = neu::GetEngine().GetTime().GetDeltaTime();

        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

		transform.rotation.y += 90 * dt;
		program->SetUniform("u_model", transform.GetMatrix());

		//view matrix
        float speed = 10.0f;
		if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A))cameraTransform.position.x -= speed * dt;
		if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D))cameraTransform.position.x += speed * dt;
		if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W))cameraTransform.position.y -= speed * dt;
		if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S))cameraTransform.position.y += speed * dt;
		if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q))cameraTransform.position.z -= speed * dt;
		if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_E))cameraTransform.position.z += speed * dt;
		glm::mat4 view = glm::lookAt(cameraTransform.position, cameraTransform.position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
        program->SetUniform("u_view", view);

      
        program->SetUniform("u_light.position", (glm::vec3)(view* glm::vec4(lightTransform.position, 1)));

        neu::GetEngine().GetRenderer().Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        // set ImGui
        ImGui::Begin("Editor");
        ImGui::Text("Hello World");
        ImGui::Text("Press 'Esc' to quit.");
        ImGui::End();
        
		model3d->Draw(GL_TRIANGLES);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        neu::GetEngine().GetRenderer().Present();
    }

    neu::GetEngine().Shutdown();

    return 0;
}
