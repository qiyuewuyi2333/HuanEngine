#pragma once

#include "HuanPCH.h"
#include "Huan/Core.h"

namespace Huan
{
enum class ShaderType
{
    None = 0,
    Pipeline,
    Vertex,
    Fragment,
    Compute,
    Geometry,
    Mesh
};
class Shader
{
  public:
    virtual ~Shader() = default;
    // ------------------------------------------------------------------------
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual unsigned int getID() const = 0;
    virtual ShaderType getType() const = 0;
    virtual Ref<std::string> getSource() const = 0;

    virtual void uploadUniformBool(const std::string& name, bool value) const = 0;
    virtual void uploadUniformInt(const std::string& name, int value) const = 0;
    virtual void uploadUniformFloat(const std::string& name, float value) const = 0;
    virtual void uploadUniformVec2(const std::string& name, const glm::vec2& value) const = 0;
    virtual void uploadUniformVec2(const std::string& name, float x, float y) const = 0;
    virtual void uploadUniformVec3(const std::string& name, const glm::vec3& value) const = 0;
    virtual void uploadUniformVec3(const std::string& name, float x, float y, float z) const = 0;
    virtual void uploadUniformVec4(const std::string& name, const glm::vec4& value) const = 0;
    virtual void uploadUniformVec4(const std::string& name, float x, float y, float z, float w) const = 0;
    virtual void uploadUniformMat2(const std::string& name, const glm::mat2& mat) const = 0;
    virtual void uploadUniformMat3(const std::string& name, const glm::mat3& mat) const = 0;
    virtual void uploadUniformMat4(const std::string& name, const glm::mat4& mat) const = 0;
};
} // namespace Huan