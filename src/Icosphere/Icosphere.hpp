#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include <raylib.h>
#include <raymath.h>

/*  A mesh of triangles representing a spherical surface.
    The methods here are adapted from http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html.
*/
class Icosphere {
    public:
        Icosphere();
        ~Icosphere() {};
        void Draw();
    private:
        Vector3 position;
        float radius;
        int resolution;
        Color colour;
        std::vector<Vector3> vertices;
        std::vector<Vector3> normals;
        Model model;

        struct TriIndex {
            int index0;
            int index1;
            int index2;

            TriIndex(int index0, int index1, int index2) {
                this->index0 = index0;
                this->index1 = index1;
                this->index2 = index2;
            }
        };
        int CreateNewMidpoint(int index1, int index2);
};