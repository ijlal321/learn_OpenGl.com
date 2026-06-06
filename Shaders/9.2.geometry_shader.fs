#version 330 core
out vec4 FragColor;

in vec3 texCoords;
uniform samplerCube Skybox;
void main()
{   
    // FragColor = vec4(1 - texCoords.xy, 1, 1.0);
    FragColor = vec4(texture(Skybox, texCoords).rgb, 1.0);
}