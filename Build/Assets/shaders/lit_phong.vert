#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec3 a_normal;

out VS_OUT {
    vec2 v_texcoord;
    vec3 v_position; 
    vec3 v_normal;
    mat3 v_tbn; 
} vs_out;

struct Material {
    vec3 baseColor;
    vec3 emissiveColor;
    float shininess;
    vec2 tiling;
    vec2 offset;
    uint parameters;
};

uniform Material u_material;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    
    vs_out.v_texcoord = a_texcoord * u_material.tiling + u_material.offset;

   
    mat3 normalMatrix = transpose(inverse(mat3(u_model)));
    vs_out.v_normal = normalize(normalMatrix * a_normal);

    
    vec4 worldPosition = u_model * vec4(a_position, 1.0);
    vs_out.v_position = worldPosition.xyz;

   
    gl_Position = u_projection * u_view * worldPosition;
}
