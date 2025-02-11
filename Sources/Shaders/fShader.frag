#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec3 LightColor;

vec3 ObjectColor = vec3(1.0f, 0.6f, 0.8f);

void main()
{
	FragColor = vec4(ObjectColor, 1.f);
}
