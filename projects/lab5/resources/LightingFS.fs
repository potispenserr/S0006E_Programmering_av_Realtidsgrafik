#version 330 core
out vec4 FragColor;

in vec3 lightNormal;  
in vec3 fragPos;  
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float ambientIntensity;
uniform vec3 viewPosition;

void main()
{
    vec3 ambient = ambientIntensity * lightColor;
  	
    vec3 norm = normalize(lightNormal);
    vec3 lightDirection = normalize(lightPos - fragPos);
    float distdiff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = distdiff * lightColor;
            
    float specularIntensity = 1.0;
    vec3 viewDirection = normalize(viewPosition - fragPos);
    vec3 reflectDirection = reflect(lightDirection, norm);
    float shininess = 256;
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
    vec3 combinedSpec = specularIntensity * spec * lightColor;  
    

    vec3 result = (ambient + diffuse + combinedSpec) * objectColor;
    FragColor = vec4(result, 1.0);
} 