#version 430 core

uniform sampler2D textSampler;
uniform int apply_texture;

// Inputs from vertexshader
in vec3 vColor;
in vec2 UV;

// Output color
out vec4 fragColor;

void main()
{
    if(apply_texture == 1){
        //fragColor = vec4(vColor, 1.0);
        fragColor = texture2D(textSampler, UV);
    }
    else{
    fragColor = vec4(vColor, 1.0);
    }
}
