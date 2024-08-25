#pragma once

#include "Renderer/Material/Material.h"

namespace Huan
{
class OpenGLMaterial : public Material
{
  public:
    OpenGLMaterial(const std::string& name);
    virtual ~OpenGLMaterial() = default;

    virtual void bind() const override;
    virtual void unbind() const override;
    virtual void setData(const Ref<MaterialData>& data) override;
    virtual void setShader(const Ref<Shader>& shader) override;
    virtual void setTexture(const std::string& name, const Ref<Texture>& texture) override;
    
    virtual void uploadUniformBool(const std::string& name, bool value) const override;
    virtual void uploadUniformFloat(const std::string& name, float value) const override;
    virtual void uploadUniformFloat2(const std::string& name, const glm::vec2& value) const override;
    virtual void uploadUniformFloat3(const std::string& name, const glm::vec3& value) const override;
    virtual void uploadUniformFloat4(const std::string& name, const glm::vec4& value) const override;
    virtual void uploadUniformInt(const std::string& name, int value) const override;
    virtual void uploadUniformInt2(const std::string& name, const glm::ivec2& value) const override;
    virtual void uploadUniformInt3(const std::string& name, const glm::ivec3& value) const override;
    virtual void uploadUniformInt4(const std::string& name, const glm::ivec4& value) const override;
    virtual void uploadUniformMat3(const std::string& name, const glm::mat3& matrix) const override;
    virtual void uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override;
  private:
    Ref<Shader> myShader;
    Ref<MaterialData> myData;
    std::unordered_map<std::string, Ref<Texture>> myTextures;
    std::string myName;
};
} // namespace Huan
