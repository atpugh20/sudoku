#include <GLEW/glew.h>

#include "Renderer.h"
#include "Shader.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string &filepath)
    : m_FilePath(filepath), m_RendererID(0) {
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}

// UNIFORMS //

void Shader::SetUniform1i(const std::string &name, int value) {
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string &name, float value) {
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}


int Shader::GetUniformLocation(const std::string &name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!\n";

    m_UniformLocationCache[name] = location;
    return location;
}

// BUILDING THE SHADER //

unsigned int Shader::CompileShader(unsigned int type, const std::string &source) {
    /*
    * Takes a string of shader code, compiles it, then returns its ID
    */
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    // Error Handling
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    /*
    * Combines the vertex and fragment shaders into one
    * program, the returns the program.
    */

    // Compile the two shaders
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    // Create program from the shaders
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    // Delete both shaders and return program
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    return program;
}

ShaderProgramSource Shader::ParseShader(const std::string &filepath) {
    /*
    * Grabs the vertex and fragment shader strings from the filepath,
    * then returns both strings as a ShaderProgramSource struct.
    */
    std::ifstream stream(filepath);  // Get file 

    // Indexes for the string stream array (ss)
    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    // Loop until the end of the file
    while (getline(stream, line)) {
        // If there is a shader
        if (line.find("#shader") != std::string::npos) {
            // Get the shader type
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}