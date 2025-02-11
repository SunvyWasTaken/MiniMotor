#version 330 core

out vec4 FragColor;

uniform vec3 LightColor;

vec3 ObjectColor = vec3(1.0f, 0.6f, 0.8f);

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0);
}
