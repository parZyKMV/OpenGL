#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec3 a_normal;

out vec2 v_texcoord;
out vec3 v_color;

uniform float u_time;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform vec3 u_ambient_light;

vec3 calculateLight()
{
    // Simple ambient light calculation
    return u_ambient_light;
}

void main()
{
    v_texcoord = a_texcoord;
    v_color = calculateLight();

    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
}
