#version 460 core

in vec3 v_color;
out vec4 f_color;

uniform float u_time;

void main()
{
    float pulse = (sin(u_time * 2.0) * 0.5) + 0.5;
    f_color = vec4(v_color * pulse, 1.0);
}
