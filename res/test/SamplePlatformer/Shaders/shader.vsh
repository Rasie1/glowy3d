#version 330 core
in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
uniform mat4 MVP;
out vec3 fragmentColor;

void main()
{
    vec4 v = vec4(vertexPosition_modelspace,1);
    gl_Position = MVP * v;

    fragmentColor = vertexColor;
}