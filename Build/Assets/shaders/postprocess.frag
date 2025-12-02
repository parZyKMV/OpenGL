#version 430

#define GRAYSCALE   (1 << 0)
#define COLORTINT   (1 << 1)
#define SCANLINE    (1 << 2)
#define GRAIN       (1 << 3)
#define INVERT      (1 << 4)
#define VIGNETTE    (1 << 5)  // custom effect

in vec2 v_texcoord;
out vec4 f_color;

uniform uint u_parameters;
uniform vec3 u_colorTint;
uniform float u_time;
uniform float u_blend;       


uniform float u_vignetteRadius;  
uniform float u_vignetteSoftness; 

uniform sampler2D u_baseMap;
float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
    vec4 color = texture(u_baseMap, v_texcoord);
    vec4 postprocess = color;

    // GRAYSCALE - use Rec.709 luminance
    if ((u_parameters & GRAYSCALE) != 0u) {
        float l = dot(postprocess.rgb, vec3(0.2126, 0.7152, 0.0722));
        postprocess = vec4(vec3(l), postprocess.a);
    }

    // COLOR TINT - multiply rgb by tint
    if ((u_parameters & COLORTINT) != 0u) {
        postprocess.rgb *= u_colorTint;
    }

    // SCANLINE - simple alternating horizontal lines
    if ((u_parameters & SCANLINE) != 0u) {
        // choose thickness and intensity via modulo, here mod 3 as example
        int y = int(floor(gl_FragCoord.y));
        if ((y % 3) != 0) {
            // darken slightly rather than full black to preserve blending
            postprocess.rgb *= 0.6;
        }
    }

    // GRAIN - multiply by a small noise value around 1.0
    if ((u_parameters & GRAIN) != 0u) {
        // use gl_FragCoord + time so grain changes over time
        float n = random(gl_FragCoord.xy + u_time);
        // map [0,1] -> [0.9,1.1] subtle grain
        float grain = mix(0.95, 1.05, n);
        postprocess.rgb *= grain;
    }

    // INVERT - invert RGB channels
    if ((u_parameters & INVERT) != 0u) {
        postprocess.rgb = vec3(1.0) - postprocess.rgb;
    }

    // VIGNETTE (custom) - darken edges based on distance from center
    if ((u_parameters & VIGNETTE) != 0u) {
        vec2 uv = v_texcoord * 2.0 - 1.0; // -1..1
        float dist = length(uv);
        // smoothstep for soft falloff: radius controls where falloff starts
        float vig = smoothstep(u_vignetteRadius, u_vignetteRadius - u_vignetteSoftness, dist);
        // vig is 0 at center, 1 at outer; darken by vig
        postprocess.rgb *= (1.0 - 0.7 * vig); // max darkening 70%
    }

    // final mix between original color and processed result
    f_color = mix(color, postprocess, clamp(u_blend, 0.0, 1.0));
}
