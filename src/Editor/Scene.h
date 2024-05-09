#pragma once

namespace Editor {

struct Sphere
{
    glm::vec3 Position{0.0f};
    float Radius = 0.5f;

    glm::vec3 Albedo{1.0f};
    float _Padding;
};

struct Scene
{
    std::vector<Sphere> Spheres;
    // Sphere Spheres[2];
};

}