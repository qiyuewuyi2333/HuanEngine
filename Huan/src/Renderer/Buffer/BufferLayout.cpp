#include "Renderer/Buffer/BufferLayout.h"

namespace Huan
{
uint32_t shaderDataTypeToSize(ShaderDataType type)
{
    switch (type)
    {
    case ShaderDataType::Float:
        return 1 * sizeof(float);
    case ShaderDataType::Float2:
        return 2 * sizeof(float);
    case ShaderDataType::Float3:
        return 3 * sizeof(float);
    case ShaderDataType::Float4:
        return 4 * sizeof(float);
    case ShaderDataType::Mat3:
        return 3 * 3 * sizeof(float);
    case ShaderDataType::Mat4:
        return 4 * 4 * sizeof(float);
    case ShaderDataType::Int:
        return 1 * sizeof(int);
    case ShaderDataType::Int2:
        return 2 * sizeof(int);
    case ShaderDataType::Int3:
        return 3 * sizeof(int);
    case ShaderDataType::Int4:
        return 4 * sizeof(int);
    case ShaderDataType::Bool:
        return 1 * sizeof(bool);
    }

    HUAN_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}
BufferLayout::BufferLayout(const std::initializer_list<BufferLayoutElement>& elements) : myElements(elements)
{
    calculateOffsetsAndStride();
}
const std::vector<BufferLayoutElement>& BufferLayout::getElements() const
{
    return myElements;
}
uint32_t BufferLayout::getStride() const
{
    return myStride;
}
void BufferLayout::calculateOffsetsAndStride()
{
    uint32_t offset = 0;
    myStride = 0;
    for (auto& element : myElements)
    {
        element.offset = offset;
        offset += element.size;
        myStride += element.size;
    }
}
std::vector<BufferLayoutElement>::iterator BufferLayout::begin()
{
    return myElements.begin();
}
std::vector<BufferLayoutElement>::iterator BufferLayout::end()
{
    return myElements.end();
}
std::vector<BufferLayoutElement>::const_iterator BufferLayout::begin() const
{
    return myElements.begin();
}
std::vector<BufferLayoutElement>::const_iterator BufferLayout::end() const
{
    return myElements.end();
}

} // namespace Huan