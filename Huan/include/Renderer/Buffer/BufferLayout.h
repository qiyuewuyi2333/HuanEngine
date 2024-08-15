#pragma once
#include "HuanPCH.h"
#include "util/Log.h"
#include "Huan/Core.h"
namespace Huan
{
enum class ShaderDataType
{
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool,
};
uint32_t HUAN_API shaderDataTypeToSize(ShaderDataType type);

struct HUAN_API BufferLayoutElement
{
  public:
    ShaderDataType type;
    std::string name;
    uint32_t size;
    uint32_t offset;
    bool shouldNormalized;
    BufferLayoutElement()
    {
    }
    BufferLayoutElement(ShaderDataType _type, std::string _name, bool normalized = false)
        : type(_type), name(_name), size(shaderDataTypeToSize(_type)), offset(0), shouldNormalized(normalized)
    {
    }
    uint32_t getComponentCount() const
    {
        switch (type)
        {
        case ShaderDataType::Float:
            return 1;
        case ShaderDataType::Float2:
            return 2;
        case ShaderDataType::Float3:
            return 3;
        case ShaderDataType::Float4:
            return 4;
        case ShaderDataType::Mat3:
            return 3 * 3;
        case ShaderDataType::Mat4:
            return 4 * 4;
        case ShaderDataType::Int:
            return 1;
        case ShaderDataType::Int2:
            return 2;
        case ShaderDataType::Int3:
            return 3;
        case ShaderDataType::Int4:
            return 4;
        case ShaderDataType::Bool:
            return 1;
        }

        HUAN_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
};
class HUAN_API BufferLayout
{
  public:
    BufferLayout() = default;
    BufferLayout(const std::initializer_list<BufferLayoutElement>& elements);
    const std::vector<BufferLayoutElement>& getElements() const;
    uint32_t getStride() const;

    std::vector<BufferLayoutElement>::iterator begin();
    std::vector<BufferLayoutElement>::iterator end();
    std::vector<BufferLayoutElement>::const_iterator begin() const;
    std::vector<BufferLayoutElement>::const_iterator end() const;

  private:
    void calculateOffsetsAndStride();

  private:
    std::vector<BufferLayoutElement> myElements;
    uint32_t myStride = 0;
};
} // namespace Huan