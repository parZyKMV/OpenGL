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
        {{-0.5f,-0.5f, 0.0f}, {1, 0, 0}, {0,0}},
        {{ 0.0f, 0.5f, 0.0f}, {0, 1, 0}, {0.05f,1.0f}},
        {{ 0.5f, -0.5f, 0.0f}, {0, 0, 1}, {1,1}},
        {{ 0.0f, -0.5f, 0.0f}, {1, 1, 0}, {0.5f,0.5f}},
    };

	std::vector<GLuint> indices{ 0,1,2 };

    GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* vertices.size(), vertices.data(), GL_STATIC_DRAW);

    GLuint ibo;
	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* indices.size(), indices.data(), GL_STATIC_DRAW);


    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));


 //   GLuint vbo[3];
 //   glGenBuffers(3, vbo);

 //   // Vertex positions
 //   glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
 //   glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec3) * points.size(), points.data(), GL_STATIC_DRAW);

 //   // Vertex colors
 //   glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
 //   glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);

	////Vertex buffer(texcoords)
 //   glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
 //   glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec3) * points.size(), points.data(), GL_STATIC_DRAW);


 //   // Position attribute
 //   glEnableVertexAttribArray(0);
 //   glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
 //   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

 //   // Color attribute
 //   glEnableVertexAttribArray(1);
 //   glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
 //   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//// Texcoord attribute
 //   glEnableVertexAttribArray(2);
 //   glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
 //   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    // === VERTEX SHADER ===
    //std::string vs_source;
    //neu::file::ReadTextFile("shaders/basic.vert", vs_source);
    //const char* vs_cstr = vs_source.c_str();

    //GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vs, 1, &vs_cstr, NULL);
    //glCompileShader(vs);

    //// Check vertex shader compile errors
    //GLint success;
    //char infoLog[512];
    //glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    //if (!success) {
    //    glGetShaderInfoLog(vs, 512, NULL, infoLog);
    //    LOG_ERROR("Vertex Shader compilation failed:\n{}", infoLog);
    //}

    //// === FRAGMENT SHADER ===
    //std::string fg_source;
    //neu::file::ReadTextFile("shaders/basic.frag", fg_source);
    //const char* fg_cstr = fg_source.c_str();

    //GLuint fg = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fg, 1, &fg_cstr, NULL);
    //glCompileShader(fg);

    //// Check fragment shader compile errors
    //glGetShaderiv(fg, GL_COMPILE_STATUS, &success);
    //if (!success) {
    //    glGetShaderInfoLog(fg, 512, NULL, infoLog);
    //    LOG_ERROR("Fragment Shader compilation failed:\n{}", infoLog);
    //}

    // Create shaders using the new Shader class
    auto vs = std::make_shared<neu::Shader>();
    vs->Load("shaders/basic.vert", GL_VERTEX_SHADER);

    auto fs = std::make_shared<neu::Shader>();
    fs->Load("shaders/basic.frag", GL_FRAGMENT_SHADER);

    // Crea y enlaza el programa
    auto program = std::make_shared<neu::Program>();
    program->AttachShader(vs);
    program->AttachShader(fs);
    program->Link();
    program->Use();

    // Ejemplo: enviar el tiempo a un uniform
    float timeValue = 1.5f;
    program->SetUniform("u_time", timeValue);
    
    //textures
    neu::res_t<neu::Texture> texture = neu::Resources().Get<neu::Texture>("textures/cat.jpg");

    // === MAIN LOOP ===
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
        }

        neu::GetEngine().Update();

        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        //glUniform1f(uniform, neu::GetEngine().GetTime().GetTime());

        neu::vec3 color{ 0, 0, 0 };
        /*neu::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);*/
        neu::GetEngine().GetRenderer().Clear();

        glBindVertexArray(vao);
       /* glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)points.size());*/
		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);


        neu::GetEngine().GetRenderer().Present();
    }

    neu::GetEngine().Shutdown();

    return 0;
}
