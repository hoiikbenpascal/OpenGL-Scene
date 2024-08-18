#version 430 core

// Material properties
uniform vec3 mat_ambient;
uniform vec3 mat_diffuse;
uniform vec3 mat_specular;
uniform float mat_power;
uniform sampler2D textSampler;
uniform int apply_texture;
uniform vec3 light_pos;
uniform vec3 light_color = vec3(1);

// Input from vertex shader
in VS_OUT
{
    vec3 normal;
    vec3 view;
    vec3 frag_pos;
} fs_in;

in vec2 UV;

// Output color
out vec4 fragColor;

void main()
{
    // Normalize the incoming N, and V vectors
    vec3 N = normalize(fs_in.normal);
    vec3 V = normalize(fs_in.view);

    // calculate the light direction
    vec3 light_dir = normalize(light_pos - fs_in.frag_pos);

    vec3 ambient;
    vec3 diffuse;

    ambient = mat_ambient;
    float diff = max(dot(N, light_dir), 0.0);
    diffuse = light_color * (diff * mat_diffuse);

    vec3 R = reflect(-light_dir, N);
    float spec =  pow(max(dot(V, R), 0.0), mat_power);
    vec3 specular = light_color * (spec * mat_specular);

    // Write final color to the framebuffer

    if(apply_texture == 1){
        fragColor = vec4((ambient + diffuse + specular), 1.0f) * texture(textSampler, UV);
    }
    else{
        fragColor = vec4((ambient + diffuse + specular) * mat_ambient, 1.0);
    }
}