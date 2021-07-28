#version 330 core

in vec2 UV;

uniform sampler2D mainTexture;

void main()
{
    // multiply it by the color
    //vec3 color = vec3(1.0f, 0.5f, 0.2f);
    vec3 color = texture(mainTexture, UV ).rgb;
    //vec3 color = vec3(UV.x, UV.y, 0.2f);
    gl_FragColor = vec4(color.r,color.g,color.b, 1);
    //vec4(1.0f, 0.5f, 0.2f, 1.0f);
}