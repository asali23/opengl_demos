#version 140

in vec2 textureCoordinates;

uniform sampler2D sampler;

out vec4 finalcolor;

void main()
{
    finalcolor = texture2D(sampler, textureCoordinates.xy);
}
