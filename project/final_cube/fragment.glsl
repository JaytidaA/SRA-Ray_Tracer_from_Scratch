#version 430 core

out vec4 FragColor;       // Output color of the fragment
in vec2 TexCoord;         // Input texture coordinates passed from the vertex shader

uniform sampler2D uTexture; // Texture sampler for the 2D texture

void main()
{
    // Sample the texture using the provided texture coordinates
    FragColor = texture(uTexture, TexCoord);
}

