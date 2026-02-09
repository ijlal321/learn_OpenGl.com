#version 330 core
out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;


in vec3 fragPos;
in vec3 Normal;  


void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 result = ambient * objectColor;

    vec3 norm = normalize(Normal);

    // diffuse
    // lightPos, fragPos (both in world space)
    vec3 lightVec = normalize(lightPos - fragPos);
    float intensityFactor = max(dot(lightVec, norm), 0);
    vec3 diffuse = intensityFactor * lightColor;

    result += (intensityFactor * objectColor);

    // Specular
    float specularStrength = 0.5f;
    lightVec = normalize(lightPos - fragPos);
    vec3 viewVec = normalize(viewPos - fragPos);
    // Reflection takes first vec, pointing from light src to obj, and 2nd one pointing away from obj (Normal)
    vec3 reflectionDir = reflect(-lightVec, norm); //  this var tells, where would reflection go
    float specularInternsity = max(dot(reflectionDir, viewVec), 0);
    specularInternsity = pow(specularInternsity, 32); // 2nd value is shininess value (based on material). 
    vec3 specular = specularStrength * specularInternsity * lightColor;

    result += (specular * objectColor);


    FragColor = vec4(result, 1.0);
}