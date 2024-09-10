#ifndef HAZELENGINE_SHADER_H
#define HAZELENGINE_SHADER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader{
public:
    GLuint ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void use() {glUseProgram(ID);}
    void setMat4(const std::string& name, const glm::mat4& mat){
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void setVec3(const std::string& name, const glm::vec3& vec){
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
    }

private:
    std::string loadShaderCode(const char* shaderPath);
    GLuint compileShader(GLenum type, const char* source);
};

#endif //HAZELENGINE_SHADER_H