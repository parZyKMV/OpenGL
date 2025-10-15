#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_color;
layout (location = 2) in vec2 a_texcoord;


out vec3 v_color;
out vec2 v_texcoord;
uniform float u_time;

void main()
{
    float frequency = 3.0;
    float amplitude = 0.1;

    vec3 position = a_position;
    position.y += sin(u_time * frequency + position.x) * amplitude;

    v_color = a_color;
    v_texcoord = a_texcoord;
    gl_Position = vec4(position, 1.0);
}
