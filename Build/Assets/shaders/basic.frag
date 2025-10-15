#version 460 core

in vec3 v_color;
in vec2 v_texcoord;

out vec4 f_color;

uniform float u_time;
uniform sampler2D u_texture;

void main()
{
    float pulse = (sin(u_time * 2.0) * 0.5) + 0.5;
    f_color = vec4(v_color * pulse, 1.0);

    f_color =  texture(u_texture, v_texcoord);
}
