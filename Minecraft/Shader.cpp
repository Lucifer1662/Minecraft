#include "Shader.h"
#include "GL/glew.h"
#include <iostream>
#include <fstream>
#include <string>
#include <glm/glm.hpp>

unsigned int loadShader(std::string source, unsigned int shaderType) {
    auto shader = glCreateShader(shaderType);
    auto d = source.c_str();
    glShaderSource(shader, 1, (const GLchar* const*)&d, NULL);
    glCompileShader(shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return shader;
}

std::string fromFile(const std::string& filePath) {

    std::string content;
    std::string line;
    std::ifstream myfile(filePath);
    if (myfile.is_open())
    {
        while (std::getline(myfile, line))
        {
            content += line + '\n';
        }
        myfile.close();
    }
    return content;
}

bool Shader::fragmentShaderFromFile(const std::string& fileName)
{
    auto f = loadShader(fromFile(fileName), GL_FRAGMENT_SHADER);
    if (f != 0) {
        fragement = f;
    }
    return f != 0;
}

bool Shader::vertexShaderFromFile(const std::string& fileName)
{


    auto f = loadShader(fromFile(fileName), GL_VERTEX_SHADER);
    if (f != 0) {
        vertex = f;
    }
    return f != 0;
}

bool Shader::create()
{
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragement);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
    }
    return success;
}

void Shader::bind()
{
    glUseProgram(program);
}

void Shader::setTextureUnit(const std::string& name, unsigned int unit)
{
    glUseProgram(program);
    GLint imageLoc = glGetUniformLocation(program, name.c_str());
    glUniform1i(imageLoc, unit);
}

void Shader::setUnifromMat4(const std::string& name, const glm::mat4& matrix)
{
    glUseProgram(program);
    GLint matrixloc = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(matrixloc, 1, GL_FALSE, &matrix[0][0]);
}

Shader::~Shader()
{
    glDeleteShader(vertex);
    glDeleteShader(fragement);
    glDeleteProgram(program);
}


