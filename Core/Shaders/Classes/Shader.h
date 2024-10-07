#ifndef HAZELENGINE_SHADER_H
#define HAZELENGINE_SHADER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader{
public:
    GLuint ID;

    Shader(const std::string& vertexPath, const std::string& fragmentPath) {
        std::string vertexCode = loadShaderCode(vertexPath);
        std::string fragmentCode = loadShaderCode(fragmentPath);

        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode.c_str());
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

        ID = glCreateProgram();

        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);

        // Verificar errores de enlace
        GLint success;
        GLchar infoLog[512];
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void use() const { glUseProgram(ID); }

    void setMat4(const std::string& name, const glm::mat4& mat) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setVec3(const std::string& name, const glm::vec3& vec) const {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
    }

private:
    std::string loadShaderCode(const std::string& shaderPath){
        std::ifstream shaderFile(shaderPath);
        if (!shaderFile.is_open()){
            std::cerr << "Error al abrir el archivo: " << shaderPath << std::endl;
        }

        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        return shaderStream.str();
    }

    GLuint compileShader(GLenum type, const char* source){
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        // Verificar errores de compilación
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        return shader;
    }
};

#endif