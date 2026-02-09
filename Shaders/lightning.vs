#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vcolor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightColor;

void main()
{
   vcolor = aColor * lightColor;
   gl_Position = projection * view * model * vec4(aPos, 1.0);
};