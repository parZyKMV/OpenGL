#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec3 a_normal;

out vec2 v_texcoord;
out vec3 v_position; 
out vec3 v_normal;

struct Material {
    sampler2D baseMap;
    vec3 baseColor;
    vec3 emissiveColor;
    float shininess;
    vec2 tiling;
    vec2 offset;
};

uniform Material u_material;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    v_texcoord = a_texcoord * u_material.tiling + u_material.offset;

    
    v_position = vec3(u_model * vec4(a_position, 1.0));
    v_normal = normalize(mat3(transpose(inverse(u_model))) * a_normal);

    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
}
