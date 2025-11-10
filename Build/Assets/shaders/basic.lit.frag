#version 460 core

in VS_OUT {
    vec2 texcoord;
    vec3 color;
} fs_in;

uniform sampler2D u_texture;

out vec4 f_color;

void main()
{
    //vec3 color = u_ambient_light;
    //for(int i = 0; i < u_num_lights; i++)
    //{
        //vec3 light_dir = normalize(u_lights[i].position - fs_in.world_pos);
    //}


    vec3 tex = texture(u_texture, fs_in.texcoord).rgb;
    //f_color = vec4(tex * fs_in.color, 1.0);
}
