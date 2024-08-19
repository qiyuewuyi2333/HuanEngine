#include "Platform/OpenGL/OpenGLShader.h"
#include "Huan/Core.h"
#include "util/Log.h"

namespace Huan
{

static GLenum shaderTypeFromString(const std::string& type)
{
    if (type == ".vert")
        return GL_VERTEX_SHADER;
    if (type == ".frag" || type == ".pixel")
        return GL_FRAGMENT_SHADER;

    HUAN_CORE_ASSERT(false, "Unknown shader type!");
    return 0;
}

OpenGLShader::OpenGLShader(const std::string& filepath)
{
    readFile(filepath);
    compile();
}
OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath)
{
    // TODO
    readFile(vertexPath);
    readFile(fragmentPath);
    compile();
}

void OpenGLShader::compile()
{
    // TODO
    GLuint program = glCreateProgram();
    HUAN_CORE_ASSERT(program, "ERROR::SHADER::PROGRAM::COMPILATION_FAILED");
    HUAN_CORE_ASSERT(shaderSources.size() <= 2, "ERROR::SHADER::PROGRAM::TOO_MANY_SHADERS");
    std::array<GLuint, 2> shaderIDs;
    int index = 0;
    for (auto& shader : shaderSources)
    {
        GLenum type = shader.first;
        GLuint shaderID = glCreateShader(type);

        const std::string& source = *(shader.second);
        const GLchar* sourceCStr = source.c_str();
        glShaderSource(shaderID, 1, &sourceCStr, 0);
        glCompileShader(shaderID);
        checkCompileErrors(shaderID, type);
        HUAN_CORE_TRACE("Compiled shader, ID: {}\n",shaderID);
        glAttachShader(program, shaderID);
        glDeleteShader(shaderID);
        shaderIDs[index++] = shaderID;
    }
    myRendererID = program;
    glLinkProgram(program);
    checkCompileErrors(program, GL_PROGRAM);
    HUAN_CORE_TRACE("Linked shader program, ID: {}\n",program);
    for (auto& shader : shaderIDs)
        glDetachShader(program, shader);
}
void OpenGLShader::readFile(const std::string& filepath)
{
    // TODO
    Ref<std::string> code;
    std::filesystem::path p(filepath);
    std::ifstream in(filepath, std::ios::in | std::ios::binary);
    in.exceptions(std::ios::failbit | std::ios::badbit);
    try
    {
        std::stringstream ss;
        ss << in.rdbuf();
        in.close();
        code = std::make_shared<std::string>(ss.str());
    }
    catch (std::ifstream::failure& e)
    {
        HUAN_CORE_ERROR("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: {}", e.what());
    }
    shaderSources[shaderTypeFromString(p.extension().string())]  = code;
    myName = p.stem().string();

}
void OpenGLShader::bind() const
{
    glUseProgram(myRendererID);
}
void OpenGLShader::unbind() const
{
    glUseProgram(0);
}

void OpenGLShader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(myRendererID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void OpenGLShader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(myRendererID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void OpenGLShader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(myRendererID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void OpenGLShader::setVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(myRendererID, name.c_str()), 1, &value[0]);
}
void OpenGLShader::setVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(myRendererID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void OpenGLShader::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(myRendererID, name.c_str()), 1, &value[0]);
}
void OpenGLShader::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(myRendererID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void OpenGLShader::setVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(myRendererID, name.c_str()), 1, &value[0]);
}
void OpenGLShader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(myRendererID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void OpenGLShader::setMat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(myRendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void OpenGLShader::setMat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(myRendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void OpenGLShader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(myRendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void OpenGLShader::checkCompileErrors(GLuint shader, GLenum type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != GL_PROGRAM)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            HUAN_CORE_ERROR("ERROR::SHADER_COMPILATION_ERROR of type: {}\n", type);
            HUAN_CORE_ASSERT(false, "ERROR info: {}\n\n -- --------------------------------------------------- -- ", infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            HUAN_CORE_ERROR("ERROR::PROGRAM_LINKING_ERROR of type: {}\n", type);
            HUAN_CORE_ASSERT(false, "ERROR info: {}\n\n -- --------------------------------------------------- -- ", infoLog);
        }
    }
}
} // namespace Huan