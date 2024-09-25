#version 430 core

in vec2 UV;

uniform sampler2D textSampler;

// Output color
out vec4 fragColor;

void main()
{
    // Write final color to the framebuffer
    fragColor = texture2D(textSampler, UV);
}