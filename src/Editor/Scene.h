#pragma once

namespace Editor {

struct Material
{
    glm::vec3 Albedo {1.0f};
    float Roughness = 1.0f;
    float Metallic = 0.0f;
    float Emission = 0.0f;
};

struct Sphere
{
    glm::vec3 Position {0.0f};
    float Radius = 0.5f;
    Material Material;
    glm::vec2 _Padding;
};

struct Scene
{
    std::vector<Sphere> Spheres;
};

}