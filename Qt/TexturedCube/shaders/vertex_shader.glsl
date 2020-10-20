#version 140

in vec3 position;
in vec2 texCoords;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec2 textureCoordinates;

void main()
{
    textureCoordinates = texCoords;
    gl_Position = Projection * View * Model * vec4(position.xyz, 1);
}
