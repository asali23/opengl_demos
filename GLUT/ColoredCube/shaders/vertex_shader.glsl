#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec4 fragColor;

void main()
{
    fragColor = vec4(color.xyz, 1);
    gl_Position = Projection * View * Model * vec4(position.xyz, 1);
}
