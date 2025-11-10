#version 460 core

in vec2 v_texcoord;
in vec3 v_position;
in vec3 v_normal;

out vec4 f_color;

struct Light {
    vec3 position;
    vec3 color;
};

struct Material {
    sampler2D baseMap;
    vec3 baseColor;
    float shininess;
    vec2 tiling;
    vec2 offset;
};

uniform Light u_light;
uniform vec3 u_ambient_light;
uniform vec3 u_viewPosition;
uniform Material u_material;

vec3 calculateLight(in vec3 position, in vec3 normal) {
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(u_light.position - position);
    vec3 view_dir = normalize(u_viewPosition - position);

    
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * u_light.color;

    
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), u_material.shininess);
    vec3 specular = spec * u_light.color;

    
    return u_ambient_light + diffuse + specular;
}

void main() {
    vec3 lighting = calculateLight(v_position, v_normal);
    vec3 color = lighting * u_material.baseColor;
    vec4 texColor = texture(u_material.baseMap, v_texcoord);
    f_color = vec4(texColor.rgb * color, texColor.a);
}
