#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <Math.hpp>

using namespace std;

/*  A mesh of triangles representing a spherical surface.
    The methods here are adapted from http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html.
*/
class Icosphere {
    public:
        Icosphere();
        ~Icosphere() {};
        void Draw(vec3 position, double radius, Color colour);
        void SetResolution(int resolution);
    private:
        int resolution;
        vector<vec3> vertices;
        vector<vec3> normals;
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
        vector<TriIndex> triangles;
        
        void GenerateModel();
        int CreateNewMidpoint(int index1, int index2);
};