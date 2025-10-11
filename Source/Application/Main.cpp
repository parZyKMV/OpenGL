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
    { 0.0f,  0.5f, 0.0f },  // top
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
     {1, 0, 0},  // rojo
     {1, 0.5, 0}, // naranja
     {1, 1, 0},   // amarillo
     {0, 1, 0},   // verde
     {0, 1, 1},   // cian
     {0, 0, 1},   // azul
     {0.5, 0, 1}, // violeta
     {1, 0, 1},   // magenta
     {1, 0, 0.5}, // rosado
     {1, 0, 0}    // rojo (cierra el ciclo)
    };


    GLuint vbo[2];
    glGenBuffers(2, vbo);

    // Vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec3) * points.size(), points.data(), GL_STATIC_DRAW);

    // Vertex colors
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Position attribute
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Color attribute
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // === VERTEX SHADER ===
    std::string vs_source;
    neu::file::ReadTextFile("shaders/basic.vert", vs_source);
    const char* vs_cstr = vs_source.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_cstr, NULL);
    glCompileShader(vs);

    // Check vertex shader compile errors
    GLint success;
    char infoLog[512];
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        LOG_ERROR("Vertex Shader compilation failed:\n{}", infoLog);
    }

    // === FRAGMENT SHADER ===
    std::string fg_source;
    neu::file::ReadTextFile("shaders/basic.frag", fg_source);
    const char* fg_cstr = fg_source.c_str();

    GLuint fg = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fg, 1, &fg_cstr, NULL);
    glCompileShader(fg);

    // Check fragment shader compile errors
    glGetShaderiv(fg, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fg, 512, NULL, infoLog);
        LOG_ERROR("Fragment Shader compilation failed:\n{}", infoLog);
    }

    // === SHADER PROGRAM ===
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fg);
    glLinkProgram(program);

    // Check program link errors
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        LOG_ERROR("Shader Program linking failed:\n{}", infoLog);
    }

    // Use the program before requesting uniforms
    glUseProgram(program);

    // === UNIFORM ===
    GLuint uniform = glGetUniformLocation(program, "u_time");
    ASSERT(uniform != -1);

    // === MAIN LOOP ===
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
        }

        neu::GetEngine().Update();

        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        glUniform1f(uniform, neu::GetEngine().GetTime().GetTime());

        neu::vec3 color{ 0, 0, 0 };
        neu::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        neu::GetEngine().GetRenderer().Clear();

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)points.size());


        neu::GetEngine().GetRenderer().Present();
    }

    neu::GetEngine().Shutdown();

    return 0;
}
