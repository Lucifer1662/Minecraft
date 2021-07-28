#version 330 core
layout (location = 0) in vec3 aPos;
layout(location = 1) in vec2 inUv;

out vec2 UV;

uniform mat4 camera;

void main()
{
    UV = inUv;
    gl_Position = camera * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}