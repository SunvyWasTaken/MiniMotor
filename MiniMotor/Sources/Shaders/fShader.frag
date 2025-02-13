#version 330 core

struct Material
{
    sampler2D Diffuse;
    sampler2D Specular;
    float shininess;
};

struct Light
{
    vec3 direction;
    vec3 lightColor;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoords;
in vec3 FragPos; 
in vec3 Normal;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

out vec4 FragColor;

void main()
{
    // ambient
  	vec3 ambient = light.ambient * vec3(texture(material.Diffuse, TexCoords));

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.Diffuse, TexCoords));
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specColor = vec3(texture(material.Diffuse, TexCoords)) * vec3(texture(material.Specular, TexCoords));
    vec3 specular = light.specular * spec * specColor;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
