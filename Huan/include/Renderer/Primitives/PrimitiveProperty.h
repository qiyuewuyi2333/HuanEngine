#pragma once

#include "Renderer/Texture/Texture.h"
#include "Huan/Core.h"
#include "glm/fwd.hpp"
namespace Huan
{
// 2D shapes properties

struct QuadProperty
{
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec4 color= glm::vec4(1.0f);
    glm::vec2 size = glm::vec2(1.0f);
    glm::vec3 rotation = glm::vec3(0.0f);

    Ref<Texture> texture = nullptr;
    /**
     * @brief The Scale factor of the texture coordinates
     * 
     */
    float tilingFactor = 1.0f;
    // QuadProperty(const glm::vec3& position = glm::vec3(0.0f), const glm::vec4& color = glm::vec4(1.0f), const glm::vec2& size = glm::vec2(1.0f), const glm::vec3& rotation = glm::vec3(0.0f), const Ref<Texture>& texture = nullptr, float tilingFactor = 1.0f) : position(position), color(color), size(size), rotation(rotation), texture(texture), tilingFactor(tilingFactor) {}
};
struct TriangleProperty
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 size;
    glm::vec3 rotation;
    Ref<Texture> texture;
    float tilingFactor;
};
struct CircleProperty
{
    glm::vec3 position;
    glm::vec4 color;
    float radius;
    float thickness;
    float fade;
};

struct CuboidProperty
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec3 size;
    glm::vec3 rotation;
    Ref<Texture> texture;
    float tilingFactor;

};
} // namespace Huan