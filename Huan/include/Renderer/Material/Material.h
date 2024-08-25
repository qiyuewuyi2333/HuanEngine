#pragma once
#include "Huan/Core.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture/Texture.h"

namespace Huan
{

struct MaterialData
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    float reflectivity;
    float refraction;
};
class HUAN_API Material
{
  public:
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual void setData(const Ref<MaterialData>& data) = 0;
    virtual void setShader(const Ref<Shader>& shader) = 0;
    virtual void setTexture(const std::string& name, const Ref<Texture>& texture) = 0;

    // uniform
    virtual void uploadUniformBool(const std::string& name, bool value) const = 0;
    virtual void uploadUniformFloat(const std::string& name, float value) const = 0;
    virtual void uploadUniformFloat2(const std::string& name, const glm::vec2& value) const = 0;
    virtual void uploadUniformFloat3(const std::string& name, const glm::vec3& value) const = 0;
    virtual void uploadUniformFloat4(const std::string& name, const glm::vec4& value) const = 0;
    virtual void uploadUniformInt(const std::string& name, int value) const = 0;
    virtual void uploadUniformInt2(const std::string& name, const glm::ivec2& value) const = 0;
    virtual void uploadUniformInt3(const std::string& name, const glm::ivec3& value) const = 0;
    virtual void uploadUniformInt4(const std::string& name, const glm::ivec4& value) const = 0;
    virtual void uploadUniformMat3(const std::string& name, const glm::mat3& matrix) const = 0;
    virtual void uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const = 0;

};
} // namespace Huan