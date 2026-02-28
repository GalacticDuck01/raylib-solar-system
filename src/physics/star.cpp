#include "star.hpp"
#include <stdint.h>
#include <unordered_map>
#include <vector>

#include "raymath.h"
#include "maths/constants.hpp"
#include "utils/utils.hpp"

Star::Star(Vector3 position, float radius, unsigned int nDivisions) {
    setPosition(position);

    if (radius <= 0) {
        warning("[Star::Star] Radius must be +ve. Defaulting to 1.");
        radius = 1;
    }
    this->radius = radius;

    generateIcosphereMesh(nDivisions);

    setTint(YELLOW);
}

void Star::generateIcosphereMesh(unsigned int nDivisions) {
    const float t = GOLDEN_RATIO;

    std::string logMsg = "[Star] Generating icosphere mesh with radius " + std::to_string(radius) + " and " + std::to_string(nDivisions) + " subdivisions...";
    log(logMsg);

    std::vector<Vector3> vertices = {
        {-1,  t,  0},
        { 1,  t,  0},
        {-1, -t,  0},
        { 1, -t,  0},

        { 0, -1,  t},
        { 0,  1,  t},
        { 0, -1, -t},
        { 0,  1, -t},

        { t,  0, -1},
        { t,  0,  1},
        {-t,  0, -1},
        {-t,  0,  1}
    };

    log("[Star] Normalizing vertices...");

    for (unsigned int iv = 0; iv < vertices.size(); iv++) {
        vertices[iv] = Vector3Normalize(vertices[iv]);
    }

    log("[Star] Subdividing triangles...");

    std::vector<unsigned int> indices = {
         0, 11,  5,
         0,  5,  1,
         0,  1,  7,
         0,  7, 10,
         0, 10, 11,

         1,  5,  9,
         5, 11,  4,
        11, 10,  2,
        10,  7,  6,
         7,  1,  8,

         3,  9,  4,
         3,  4,  2,
         3,  2,  6,
         3,  6,  8,
         3,  8,  9,

         4,  9,  5,
         2,  4, 11,
         6,  2, 10,
         8,  6,  7,
         9,  8,  1

    };

    log("[Star] Caching midpoints...");

    auto makeKey = [](unsigned int a, unsigned int b) {
        const uint64_t minIndex = std::min(a, b);
        const uint64_t maxIndex = std::max(a, b);
        return (minIndex << 32) | maxIndex;
    };

    for (unsigned int iDivision = 0; iDivision < nDivisions; iDivision++) {
        std::unordered_map<uint64_t, unsigned int> midpointCache;
        std::vector<unsigned int> newIndices;
        newIndices.reserve(indices.size() * 4);

        auto midpoint = [&](unsigned int a, unsigned int b) {
            const uint64_t key = makeKey(a, b);
            const auto found = midpointCache.find(key);
            if (found != midpointCache.end()) {
                return found->second;
            }

            Vector3 mid = Vector3Normalize(Vector3Add(vertices[a], vertices[b]));
            const unsigned int index = (unsigned int)vertices.size();
            vertices.push_back(mid);
            midpointCache.emplace(key, index);
            return index;
        };

        for (unsigned int i = 0; i < indices.size(); i += 3) {
            const unsigned int i0 = indices[i];
            const unsigned int i1 = indices[i + 1];
            const unsigned int i2 = indices[i + 2];

            const unsigned int a = midpoint(i0, i1);
            const unsigned int b = midpoint(i1, i2);
            const unsigned int c = midpoint(i2, i0);

            newIndices.push_back(i0); newIndices.push_back(a); newIndices.push_back(c);
            newIndices.push_back(i1); newIndices.push_back(b); newIndices.push_back(a);
            newIndices.push_back(i2); newIndices.push_back(c); newIndices.push_back(b);
            newIndices.push_back(a);  newIndices.push_back(b); newIndices.push_back(c);
        }

        indices.swap(newIndices);
    }

    log("[Star] Scaling vertices by radius...");

    for (unsigned int iv = 0; iv < vertices.size(); iv++) {
        vertices[iv] = Vector3Scale(vertices[iv], radius);
    }

    log("[Star] Creating mesh...");

    Mesh mesh = { 0 };
    mesh.triangleCount = indices.size() / 3;
    mesh.vertexCount = 3*mesh.triangleCount;
    mesh.vertices = (float*)MemAlloc(mesh.vertexCount*3*sizeof(float));
    mesh.normals  = (float*)MemAlloc(mesh.vertexCount*3*sizeof(float));

    for (unsigned int i = 0; i < indices.size(); i++) {
        const Vector3& vertex = vertices[indices[i]];
        mesh.vertices[3*i]     = vertex.x;
        mesh.vertices[3*i + 1] = vertex.y;
        mesh.vertices[3*i + 2] = vertex.z;

        mesh.normals[3*i]     = vertex.x / radius;
        mesh.normals[3*i + 1] = vertex.y / radius;
        mesh.normals[3*i + 2] = vertex.z / radius;
    }

    log("[Star] Loading model from mesh...");

    setMesh(mesh);

    log("[Star] Generated icosphere mesh with " + std::to_string(mesh.vertexCount) + " vertices and " + std::to_string(mesh.triangleCount) + " triangles.");
}
