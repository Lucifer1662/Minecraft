#pragma once
#include <unordered_map>
#include "glm/glm.hpp"

struct IVec3KeyHasher
{
    size_t operator()(const glm::ivec3& k)const
    {
        return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
    }

    bool operator()(const  glm::ivec3& a, const  glm::ivec3& b)const
    {
        return a.x == b.x && a.y == b.y;
    }
};