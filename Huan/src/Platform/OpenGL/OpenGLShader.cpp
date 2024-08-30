#include "Platform/OpenGL/OpenGLShader.h"
#include "Huan/Core.h"
#include "util/Log.h"

namespace Huan
{

static GLenum shaderTypeFromString(const std::string& type)
{
    HUAN_PROFILE_FUNCTION();
    if (type == ".vert")
        return GL_VERTEX_SHADER;
    if (type == ".frag" || type == ".pixel")
        return GL_FRAGMENT_SHADER;

    HUAN_CORE_ASSERT(false, "Unknown shader type!");
    return 0;
}

OpenGLShader::OpenGLShader(const std::string& filepath)
{
    HUAN_PROFILE_FUNCTION();
    readFile(filepath);
    std::vector<unsigned int> shaderIDs = compile();
    myName = "single shader";
    myRendererID = *shaderIDs.begin();
    confirmShaderType();
}
OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath)
{
    HUAN_PROFILE_FUNCTION();
    readFile(vertexPath);
    readFile(fragmentPath);
    std::vector<unsigned int> shaderIDs = compile();
    link(shaderIDs);
}
/**
 * @brief Create a new pipeline by linking two shaders
 *
 * @param vertShader
 * @param fragShader
 */
OpenGLShader::OpenGLShader(Ref<Shader> vertShader, Ref<Shader> fragShader)
{
    HUAN_PROFILE_FUNCTION();
    HUAN_CORE_ASSERT(vertShader->getType() == ShaderType::Vertex,
                     "ERROR::SHADER::PROGRAM::VERTEX_SHADER_NOT_VERTEX_SHADER");
    HUAN_CORE_ASSERT(fragShader->getType() == ShaderType::Fragment,
                     "ERROR::SHADER::PROGRAM::FRAGMENT_SHADER_NOT_FRAGMENT_SHADER");
    shaderSources[GL_VERTEX_SHADER] = vertShader->getSource();
    shaderSources[GL_FRAGMENT_SHADER] = fragShader->getSource();
    // link two shader
    GLuint program = glCreateProgram();
    HUAN_CORE_ASSERT(program, "ERROR::SHADER::PROGRAM::COMPILATION_FAILED");
    HUAN_CORE_ASSERT(shaderSources.size() <= 2, "ERROR::SHADER::PROGRAM::TOO_MANY_SHADERS");

    glAttachShader(program, vertShader->getID());
    glAttachShader(program, fragShader->getID());

    glLinkProgram(program);
    checkCompileErrors(program, GL_PROGRAM);

    // release the ownership of shaders, but not delete them
    glDetachShader(program, vertShader->getID());
    glDetachShader(program, fragShader->getID());

    myType = ShaderType::Pipeline;
    myName = "Pipeline";
    myRendererID = program;
}

void OpenGLShader::bind() const
{
    HUAN_PROFILE_FUNCTION();
    glUseProgram(myRendererID);
}
void OpenGLShader::unbind() const
{
    HUAN_PROFILE_FUNCTION();
    glUseProgram(0);
}
unsigned int OpenGLShader::getID() const
{
    return myRendererID;
}

ShaderType OpenGLShader::getType() const
{
    return myType;
}
Ref<std::string> OpenGLShader::getSource() const
{
    HUAN_CORE_ASSERT(shaderSources.size() == 1, "ERROR::SHADER::PROGRAM::TOO_MANY_SHADERS")
    return shaderSources.begin()->second;
}
void OpenGLShader::release(std::vector<unsigned int>& shaders)
{
    HUAN_PROFILE_FUNCTION();
    HUAN_CORE_ASSERT(myType == ShaderType::Pipeline, "ERROR::SHADER::PROGRAM::NOT_PIPELINE")
}
void OpenGLShader::link(std::vector<unsigned int>& shaders)
{
    HUAN_PROFILE_FUNCTION();
    GLuint program = glCreateProgram();
    HUAN_CORE_ASSERT(program, "ERROR::SHADER::PROGRAM::COMPILATION_FAILED");
    HUAN_CORE_ASSERT(shaderSources.size() <= 2, "ERROR::SHADER::PROGRAM::TOO_MANY_SHADERS");

    for (auto& shader : shaders)
        glAttachShader(program, shader);

    glLinkProgram(program);
    checkCompileErrors(program, GL_PROGRAM);
    HUAN_CORE_TRACE("Linked shader program, ID: {}\n", program);
    for (auto& shader : shaders)
        glDetachShader(program, shader);
    myRendererID = program;
    myType = ShaderType::Pipeline;
    myName = "Pipeline";
}

/**
 * @brief Compile all shader source has read from files, and return a vector of shader IDs
 *
 * @return std::vector<int>
 */
std::vector<unsigned int> OpenGLShader::compile()
{
    HUAN_PROFILE_FUNCTION();
    std::vector<unsigned int> shaderIDs(shaderSources.size());
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
        HUAN_CORE_TRACE("Compiled shader, ID: {}\n", shaderID);
        shaderIDs[index++] = shaderID;
    }

    return shaderIDs;
};
void OpenGLShader::readFile(const std::string& filepath)
{
    HUAN_PROFILE_FUNCTION();

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
    shaderSources[shaderTypeFromString(p.extension().string())] = code;
    myName = p.stem().string();
}
// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void OpenGLShader::checkCompileErrors(GLuint shader, GLenum type)
{
    HUAN_PROFILE_FUNCTION();
    GLint success;
    GLchar infoLog[1024];
    if (type != GL_PROGRAM)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            HUAN_CORE_ERROR("ERROR::SHADER_COMPILATION_ERROR of type: {}\nERROR info: {}\n\n --          --------------------------------------------------- -- ",
                            type, infoLog);
            HUAN_CORE_ASSERT(false, "");
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            HUAN_CORE_ERROR("ERROR::PROGRAM_LINKING_ERROR of type: {}\nERROR info: {}\n\n -- "
                            "--------------------------------------------------- -- ",
                            type, infoLog);
            HUAN_CORE_ASSERT(false, "");
        }
    }
}

void OpenGLShader::confirmShaderType()
{
    HUAN_PROFILE_FUNCTION();
    if (shaderSources.size() == 1)
    {
        if (shaderSources.begin()->first == GL_VERTEX_SHADER)
            myType = ShaderType::Vertex;
        else if (shaderSources.begin()->first == GL_FRAGMENT_SHADER)
            myType = ShaderType::Fragment;
        else
            HUAN_CORE_ASSERT(false, "ERROR::SHADER::PROGRAM::SHADER_TYPE_NOT_FOUND");
    }
    else if (shaderSources.size() == 2)
    {
        myType = ShaderType::Pipeline;
    }
}

void OpenGLShader::uploadUniformBool(const std::string& name, bool value) const
{
    HUAN_PROFILE_FUNCTION();
    glUniform1i(glGetUniformLocation(myRendererID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void OpenGLShader::uploadUniformInt(const std::string& name, int value) const
{
    HUAN_PROFILE_FUNCTION();
    glUniform1i(glGetUniformLocation(myRendererID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void OpenGLShader::uploadUniformFloat(const std::string& name, float value) const
{
    HUAN_PROFILE_FUNCTION();
    glUniform1f(glGetUniformLocation(myRendererID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void OpenGLShader::uploadUniformVec2(const std::string& name, const glm::vec2& value) const
{
    HUAN_PROFILE_FUNCTION();
    glUniform2fv(glGetUniformLocation(myRendererID, name.c_str()), 1, &value[0]);
}
void OpenGLShader::uploadUniformVec2(const std::string& name, float x, float y) const
{
    HUAN_PROFILE_FUNCTION();
    glUniform2f(glGetUniformLocation(myRendererID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void OpenGLShader::uploadUniformVec3(const std::string& name, const glm::vec3& value) const
{
    HUAN_PROFILE_FUNCTION();
    glUniform3fv(glGetUniformLocation(myRendererID, name.c_str()), 1, &value[0]);
}
void OpenGLShader::uploadUniformVec3(const std::string& name, float x, float y, float z) const
{
    HUAN_PROFILE_FUNCTION();
    glUniform3f(glGetUniformLocation(myRendererID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void OpenGLShader::uploadUniformVec4(const std::string& name, const glm::vec4& value) const
{
    HUAN_PROFILE_FUNCTION();
    glUniform4fv(glGetUniformLocation(myRendererID, name.c_str()), 1, &value[0]);
}
void OpenGLShader::uploadUniformVec4(const std::string& name, float x, float y, float z, float w) const
{
    HUAN_PROFILE_FUNCTION();
    glUniform4f(glGetUniformLocation(myRendererID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void OpenGLShader::uploadUniformMat2(const std::string& name, const glm::mat2& mat) const
{
    HUAN_PROFILE_FUNCTION();
    glUniformMatrix2fv(glGetUniformLocation(myRendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void OpenGLShader::uploadUniformMat3(const std::string& name, const glm::mat3& mat) const
{
    HUAN_PROFILE_FUNCTION();
    glUniformMatrix3fv(glGetUniformLocation(myRendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void OpenGLShader::uploadUniformMat4(const std::string& name, const glm::mat4& mat) const
{
    HUAN_PROFILE_FUNCTION();
    glUniformMatrix4fv(glGetUniformLocation(myRendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

} // namespace Huan