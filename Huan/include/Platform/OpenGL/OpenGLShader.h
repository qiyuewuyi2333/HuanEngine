#pragma once
#include "Renderer/Shader.h"
namespace Huan
{

class HUAN_API OpenGLShader : public Shader
{
  public:
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath);
    OpenGLShader(const std::string& filePath);
    OpenGLShader(Ref<Shader> vertShader, Ref<Shader> fragShader);

    // activate the shader
    // ------------------------------------------------------------------------
    virtual void bind() const override;
    virtual void unbind() const override;

    // get
    virtual unsigned int getID() const override;
    virtual ShaderType getType() const override;
    virtual Ref<std::string> getSource() const override;
    // utility uniform functions
    // ------------------------------------------------------------------------
    void uploadUniformBool(const std::string& name, bool value) const override;
    void uploadUniformInt(const std::string& name, int value) const override;
    void uploadUniformFloat(const std::string& name, float value) const override;
    void uploadUniformVec2(const std::string& name, const glm::vec2& value) const override;
    void uploadUniformVec2(const std::string& name, float x, float y) const override;
    void uploadUniformVec3(const std::string& name, const glm::vec3& value) const override;
    void uploadUniformVec3(const std::string& name, float x, float y, float z) const override;
    void uploadUniformVec4(const std::string& name, const glm::vec4& value) const override;
    void uploadUniformVec4(const std::string& name, float x, float y, float z, float w) const override;
    void uploadUniformMat2(const std::string& name, const glm::mat2& mat) const override;
    void uploadUniformMat3(const std::string& name, const glm::mat3& mat) const override;
    void uploadUniformMat4(const std::string& name, const glm::mat4& mat) const override;

  private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, GLenum type);
    void readFile(const std::string& filepath);
    std::vector<unsigned int> compile();
    void link(std::vector<unsigned int>& shaders);
    void release(std::vector<unsigned int>& shaders);
    void confirmShaderType();

  private:
    unsigned int myRendererID;
    std::string myName;
    std::unordered_map<GLenum, Ref<std::string>> shaderSources;
    ShaderType myType;
    
};
} // namespace Huan