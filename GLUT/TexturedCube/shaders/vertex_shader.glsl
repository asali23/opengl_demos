#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec2 textureCoordinates;

void main()
{
    textureCoordinates = texCoords;
    gl_Position = Projection * View * Model * vec4(position.xyz, 1);
}
