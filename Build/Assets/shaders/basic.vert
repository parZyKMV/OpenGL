#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_color;

out vec3 v_color;
uniform float u_time;

void main()
{
    float frequency = 3.0;
    float amplitude = 0.1;

    vec3 position = a_position;
    position.y += sin(u_time * frequency + position.x * 3.14) * amplitude;

    v_color = a_color;
    gl_Position = vec4(position, 1.0);
}
