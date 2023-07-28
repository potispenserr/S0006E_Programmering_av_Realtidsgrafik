#version 430 core
out vec4 FragColor;


in vec3 lightNormal;  
in vec3 fragPos;  
in vec2 TexCoordLight;
  

struct Material {
    sampler2D textureDiffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 pos;

};
  
uniform Material material;
uniform Light light;

uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float ambientIntensity;
uniform vec3 viewPosition;


void main()
{
    vec3 ambient = light.ambient * vec3(texture(material.textureDiffuse, TexCoordLight));
  	
    vec3 norm = normalize(lightNormal);
    vec3 lightDirection = normalize(lightPos - fragPos);
    float distdiff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * distdiff * vec3(texture(material.textureDiffuse, TexCoordLight));
            
    vec3 viewDirection = normalize(viewPosition - fragPos);
    vec3 reflectDirection = reflect(lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 combinedSpec = light.specular * (spec * material.specular);  
    

    vec3 result = ambient + diffuse + combinedSpec;
    FragColor = vec4(result, 1.0);
} 