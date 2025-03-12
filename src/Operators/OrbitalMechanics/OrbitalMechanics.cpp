#include "OrbitalMechanics.hpp"

#include <raymath.h>
#include <math.h>

void OrbitalMechanics::Update() {
    for (int ib = 0; ib < bodies.size(); ib++) {
        PhysicsBody& body = *bodies[ib];
        for (int io = 0; io < bodies.size(); io++) {
            if (io == ib) continue;

            PhysicsBody& other = *bodies[io];
            vec3 r = body.position - other.position;
            float distance = r.magnitude();
            vec3 rHat = r.normalised();

            vec3 F = rHat*(G*body.mass*other.mass/pow(distance, 2.0f));
            body.ApplyInstantaneousForce(F*-1.f);
            other.ApplyInstantaneousForce(F);
        }
    }
}

void OrbitalMechanics::AddBody(PhysicsBody& body) {
    bodies.push_back(&body);
}