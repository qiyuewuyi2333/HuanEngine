#include "Platform/OpenGL/Material/OpenGLMaterial.h"

namespace Huan
{
OpenGLMaterial::OpenGLMaterial(const std::string& name) : myName(name)
{
}

void OpenGLMaterial::bind() const
{
    int slot = 0;
    for (auto& [key, value] : myTextures)
    {
        value->bind(slot);
        std::string uniformName = "u_Texture" + std::to_string(slot);
        myShader->setInt(uniformName, slot);
        ++slot;
    }
    myShader->bind();
}
void OpenGLMaterial::unbind() const
{
    myShader->unbind();
}
void OpenGLMaterial::setData(const Ref<MaterialData>& data)
{
    myData = data;
}
void OpenGLMaterial::setShader(const Ref<Shader>& shader)
{
    myShader = shader;
}
void OpenGLMaterial::setTexture(const std::string& name, const Ref<Texture>& texture)
{
    myTextures[name] = texture;
}





void OpenGLMaterial::uploadUniformBool(const std::string& name, bool value) const
{
    myShader->setBool(name, value);
}
void OpenGLMaterial::uploadUniformFloat(const std::string& name, float value) const
{
    myShader->setFloat(name, value);
}
void OpenGLMaterial::uploadUniformFloat2(const std::string& name, const glm::vec2& value) const
{
    myShader->setVec2(name, value);
}
void OpenGLMaterial::uploadUniformFloat3(const std::string& name, const glm::vec3& value) const
{
    myShader->setVec3(name, value);
}
void OpenGLMaterial::uploadUniformFloat4(const std::string& name, const glm::vec4& value) const
{
    myShader->setVec4(name, value);
}
void OpenGLMaterial::uploadUniformInt(const std::string& name, int value) const
{
    myShader->setInt(name, value);
}
void OpenGLMaterial::uploadUniformInt2(const std::string& name, const glm::ivec2& value) const
{
    myShader->setVec2(name, value);
}
void OpenGLMaterial::uploadUniformInt3(const std::string& name, const glm::ivec3& value) const
{
    myShader->setVec3(name, value);
}
void OpenGLMaterial::uploadUniformInt4(const std::string& name, const glm::ivec4& value) const
{
    // TODO: for shader ivec4
    myShader->setVec4(name, value);
}
void OpenGLMaterial::uploadUniformMat3(const std::string& name, const glm::mat3& matrix) const
{
    myShader->setMat3(name, matrix);
}
void OpenGLMaterial::uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const
{
    myShader->setMat4(name, matrix);
}

} // namespace Huan
