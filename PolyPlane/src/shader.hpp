//
//  shaderLoading.hpp
//  LearningOpenGL
//
//  Created by Michael  Silk on 8/28/18.
//  Copyright © 2018 Michael  Silk. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>

using namespace std;

class Shader
{
public:
    // Constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    
    GLuint GetID() { return ID; }
    // activate the shader
    void Use();
    void SetBool(const string &name, bool value) const;
    void SetInt(const string &name, int value) const;
    void SetFloat(const string &name, float value) const;
    void SetVector(const string &name, const glm::vec2 &value) const;
    void SetVector(const string &name, float x, float y) const;
    void SetVector(const string &name, const glm::vec3 &value) const;
    void SetVector(const string &name, float x, float y, float z) const;
    void SetVector(const string &name, const glm::vec4 &value) const;
    void SetVector(const string &name, float x, float y, float z, float w) const;
    void SetMatrix(const string &name, const glm::mat2 &mat) const;
    void SetMatrix(const string &name, const glm::mat3 &mat) const;
    void SetMatrix(const string &name, const glm::mat4 &mat) const;
private:
    // The program ID
    GLuint ID;
    GLint LoadAndCompileShader(GLuint shaderID, const char* file_path);
};

#endif /* shader_hpp */
