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

    // activate the shader
    // ------------------------------------------------------------------------
    virtual void bind() const override;
    virtual void unbind() const override;
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const override;
    void setInt(const std::string& name, int value) const override;
    void setFloat(const std::string& name, float value) const override;
    void setVec2(const std::string& name, const glm::vec2& value) const override;
    void setVec2(const std::string& name, float x, float y) const override;
    void setVec3(const std::string& name, const glm::vec3& value) const override;
    void setVec3(const std::string& name, float x, float y, float z) const override;
    void setVec4(const std::string& name, const glm::vec4& value) const override;
    void setVec4(const std::string& name, float x, float y, float z, float w) const override;
    void setMat2(const std::string& name, const glm::mat2& mat) const override;
    void setMat3(const std::string& name, const glm::mat3& mat) const override;
    void setMat4(const std::string& name, const glm::mat4& mat) const override;

  private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, GLenum type);
    void compile();
    void readFile(const std::string& filepath);
    void preProcess(Ref<std::string> source);

  private:
    unsigned int myRendererID;
    std::string myName;
    std::unordered_map<GLenum, Ref<std::string>> shaderSources;
};
} // namespace Huan