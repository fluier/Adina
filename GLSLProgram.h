#pragma once

#include<glm\glm.hpp>

#include <string>

typedef unsigned int GLuint;
typedef int GLint;

namespace Adina {

    //This class handles the compilation, linking, and usage of a GLSL shader program.
    //Reference: http://www.opengl.org/wiki/Shader_Compilation
    class GLSLProgram
    {
    public:
        GLSLProgram();
        ~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);

        void linkShaders();

        void addAttribute(const std::string& attributeName);

		/// send only int value
		void setUniform1i(const std::string& uniformName, const int& value);
		/// send only float value
		void setUniform1f(const std::string& uniformName, const float& value);
		void setUniformMatrix4fv(const std::string& uniformName, const glm::mat4& value);


        void use();
        void unuse();

		void dispose();

    private:
		void compileShader(const char* source, const std::string& name, GLuint id);

		GLint getUniformLocation(const std::string& uniformName);

        int m_numAttributes;

        GLuint m_programID;

        GLuint m_vertexShaderID;
        GLuint m_fragmentShaderID;
    };

}
