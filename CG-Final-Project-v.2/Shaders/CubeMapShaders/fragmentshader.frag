#version 430 core

out vec4 fragColor;

in vec3 texCoords;

uniform samplerCube textSampler;

void main()
{    
    fragColor = texture(textSampler, texCoords);
}