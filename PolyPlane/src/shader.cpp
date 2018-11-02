#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "shader.hpp"



// Constructor builds and compiles the shader program on the fly
Shader::Shader(const char * vertex_file_path, const char * frag_file_path)
{
    // load and compile the vertex shader
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (LoadAndCompileShader(vertexShaderID, vertex_file_path) == GL_FALSE)
        return;
    
    // load and compile the fragment shader
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (LoadAndCompileShader(fragmentShaderID, frag_file_path) == GL_FALSE)
        return;
    
    // Link the program
    printf("Linking program\n");
    ID = glCreateProgram();
    glAttachShader(ID, vertexShaderID);
    glAttachShader(ID, fragmentShaderID);
    glLinkProgram(ID);
    
    // Check the program
    GLint result = GL_FALSE;
    int infoLogLength;
    glGetProgramiv(ID, GL_LINK_STATUS, &result);
    glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> programErrorMessage(infoLogLength+1);
        glGetProgramInfoLog(ID, infoLogLength, NULL, &programErrorMessage[0]);
        printf("%s\n", &programErrorMessage[0]);
    }
    
    glDetachShader(ID, vertexShaderID);
    glDetachShader(ID, fragmentShaderID);
    
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

GLint Shader::LoadAndCompileShader(GLuint shaderID, const char* file_path)
{
    // load the shader from the file path
    std::string shaderSource;
    std::ifstream shaderStream(file_path, std::ios::in);
    if (shaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderSource = sstr.str();
        shaderStream.close();
    }
    else
    {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", file_path);
        getchar();
        return GL_FALSE;
    }
    
    printf("Compiling shader : %s\n", file_path);
    char const * sourcePointer = shaderSource.c_str();
    glShaderSource(shaderID, 1, &sourcePointer , NULL);
    glCompileShader(shaderID);
    
    GLint result = GL_FALSE;
    int infoLogLength;
    
    // Check Vertex Shader
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> shaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
        printf("%s\n", &shaderErrorMessage[0]);
    }
    
    return result;
}

// activate the shader
// ------------------------------------------------------------------------
void Shader::Use()
{
    glUseProgram(ID);
}
// utility uniform functions
// ------------------------------------------------------------------------
void Shader::SetBool(const string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::SetInt(const string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::SetFloat(const string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::SetVector(const string &name, const glm::vec2 &value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVector(const string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::SetVector(const string &name, const glm::vec3 &value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVector(const string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::SetVector(const string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVector(const string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::SetMatrix(const string &name, const glm::mat2 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMatrix(const string &name, const glm::mat3 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMatrix(const string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------


