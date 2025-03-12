#include "Icosphere.hpp"

Icosphere::Icosphere() {
    resolution = 5;
    position = Vector3{0.f, 0.f, 0.f};
    radius = 1.f;
    colour = ORANGE;

    // Create the icosphere, very nicely sourced from http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
    const float t = (1.0f + sqrt(5.0f)) / 2.0f; // Golden ratio
    vertices = {
        Vector3Normalize(Vector3{-1,  t,  0}),
        Vector3Normalize(Vector3{ 1,  t,  0}),
        Vector3Normalize(Vector3{-1, -t,  0}),
        Vector3Normalize(Vector3{ 1, -t,  0}),
        Vector3Normalize(Vector3{ 0, -1,  t}),
        Vector3Normalize(Vector3{ 0,  1,  t}),
        Vector3Normalize(Vector3{ 0, -1, -t}),
        Vector3Normalize(Vector3{ 0,  1, -t}),
        Vector3Normalize(Vector3{ t,  0, -1}),
        Vector3Normalize(Vector3{ t,  0,  1}),
        Vector3Normalize(Vector3{-t,  0, -1}),
        Vector3Normalize(Vector3{-t,  0,  1})
    };

    triangles = {
        {0, 11, 5},
        {0,  5, 1},
        {0,  1, 7},
        {0,  7, 10},
        {0, 10, 11},
        {1,  5, 9},
        {5,  11, 4},
        {11, 10, 2},
        {10, 7, 6},
        {7, 1, 8},
        {3, 9, 4},
        {3, 4, 2},
        {3, 2, 6},
        {3, 6, 8},
        {3, 8, 9},
        {4, 9, 5},
        {2, 4, 11},
        {6, 2, 10},
        {8, 6, 7},
        {9, 8, 1}
    };

    int i1, i2, i3, i12, i13, i23;
    for (int i = 0; i < resolution; i++) {
        std::vector<TriIndex> newTriangles;
        for (const auto& tri : triangles) {
            i1 = tri.index0;
            i2 = tri.index1;
            i3 = tri.index2;
            i12 = CreateNewMidpoint(i1, i2);
            i13 = CreateNewMidpoint(i1, i3);
            i23 = CreateNewMidpoint(i2, i3);

            newTriangles.push_back({i1,  i12, i13});
            newTriangles.push_back({i13, i12, i23});
            newTriangles.push_back({i12,  i2, i23});
            newTriangles.push_back({i13, i23, i3});
        }
        triangles = newTriangles;
    }

    for (const auto& tri : triangles) {
        Vector3 v1 = vertices[tri.index0];
        Vector3 v2 = vertices[tri.index1];
        Vector3 v3 = vertices[tri.index2];

        Vector3 normal = Vector3CrossProduct(v2 - v1, v3 - v1);
        normal = Vector3Normalize(normal);

        normals.push_back(normal);
        normals.push_back(normal);
        normals.push_back(normal);
    }

    Mesh mesh = { 0 };
    mesh.triangleCount = triangles.size();
    mesh.vertexCount = 3*mesh.triangleCount;
    mesh.vertices = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    mesh.normals  = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));

    for (int it = 0; it < mesh.triangleCount; it++) {
        const auto& tri = triangles[it];
        mesh.vertices[9*it + 0] = vertices[tri.index0].x;
        mesh.vertices[9*it + 1] = vertices[tri.index0].y;
        mesh.vertices[9*it + 2] = vertices[tri.index0].z;
        mesh.vertices[9*it + 3] = vertices[tri.index1].x;
        mesh.vertices[9*it + 4] = vertices[tri.index1].y;
        mesh.vertices[9*it + 5] = vertices[tri.index1].z;
        mesh.vertices[9*it + 6] = vertices[tri.index2].x;
        mesh.vertices[9*it + 7] = vertices[tri.index2].y;
        mesh.vertices[9*it + 8] = vertices[tri.index2].z;

        mesh.normals[9*it + 0] = normals[tri.index0].x;
        mesh.normals[9*it + 1] = normals[tri.index0].y;
        mesh.normals[9*it + 2] = normals[tri.index0].z;
        mesh.normals[9*it + 3] = normals[tri.index1].x;
        mesh.normals[9*it + 4] = normals[tri.index1].y;
        mesh.normals[9*it + 5] = normals[tri.index1].z;
        mesh.normals[9*it + 6] = normals[tri.index2].x;
        mesh.normals[9*it + 7] = normals[tri.index2].y;
        mesh.normals[9*it + 8] = normals[tri.index2].z;
    }

    UploadMesh(&mesh, false);

    model = LoadModelFromMesh(mesh);

    // Free manually allocated memory
    // MemFree(mesh.vertices);
    // MemFree(mesh.normals);
}

int Icosphere::CreateNewMidpoint(int i1, int i2) {
    // Not found, so calculate middle point
    Vector3 v1 = vertices[i1];
    Vector3 v2 = vertices[i2];
    Vector3 midpoint = (v1 + v2) / 2.0f;
    midpoint = Vector3Normalize(midpoint);
    // Get index before adding new vertex
    // E.g. if we add the 13th vertex (the first new one), we want to return 12
    int index = vertices.size();
    vertices.push_back(midpoint);
    return index;
}

void Icosphere::Draw() {
    for (const auto& tri : triangles) {
        Vector3 v1 = vertices[tri.index0];
        Vector3 v2 = vertices[tri.index1];
        Vector3 v3 = vertices[tri.index2];

        Vector3 pointSource = {1, 1, 1};
        Vector3 avgV = (v1 + v2 + v3) / 3.0f;
        float distanceFromSource = std::max(std::max(Vector3Distance(pointSource, avgV), 0.1f), 1.0f);

        Color modifedColour = colour;
        modifedColour.r = colour.r/(distanceFromSource*distanceFromSource);
        modifedColour.g = colour.g/(distanceFromSource*distanceFromSource);
        modifedColour.b = colour.b/(distanceFromSource*distanceFromSource);

        DrawTriangle3D(v1, v2, v3, modifedColour);
    }


    // DrawModel(model, position, radius, colour);
    // DrawModelWires(model, position, radius, BLACK);
}