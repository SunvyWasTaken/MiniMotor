#version 330 core

// this code is clearly from https://learnopengl.com cuz i'm gonna learn math later.

struct Material
{
    sampler2D Diffuse;
    sampler2D Specular;
    float shininess;
};

struct Light
{
    vec3  position;
    vec3  direction;
    float cutOff;
};

struct DirLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform Material material;
uniform vec3 viewPos;

uniform DirLight dirLight;

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

out vec4 FragColor;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
     vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.Diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.Diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.Specular, TexCoords));
    return (ambient + diffuse + specular);
};

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.Diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.Diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.Specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main()
{
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // phase 1: Directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: Point lights
//    for(int i = 0; i < NR_POINT_LIGHTS; ++i)
//        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    // phase 3: Spot light
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    
    FragColor = vec4(result, 1.0);
    //FragColor = vec4(1.0);
}
