#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"

class Shader
{
public:
    // the program ID
    unsigned int ID;
  
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void Shader::setVec2(const std::string &name, const glm::vec2 &value) const;
    void Shader::setVec2(const std::string &name, float x, float y) const;
    void Shader::setVec3(const std::string &name, const glm::vec3 &value) const;
    void Shader::setVec3(const std::string &name, float x, float y, float z) const;
    void Shader::setVec4(const std::string &name, const glm::vec4 &value) const;
    void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const;
    void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const;
    void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const;
    void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const;
};
  