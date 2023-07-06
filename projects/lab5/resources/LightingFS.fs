#version 330 core
out vec4 FragColor;

in vec3 lightNormal;  
in vec3 fragPos;  
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float ambientIntensity;

void main()
{
    vec3 ambient = ambientIntensity * lightColor;
  	
    vec3 norm = normalize(lightNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float distdiff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = distdiff * lightColor;
            
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
} 