#include "OrbitalMechanics.hpp"

#include <raymath.h>
#include <math.h>

void OrbitalMechanics::Update(float deltaTime) {
    timeSinceUpdate += GetFrameTime();
    stepsPerUpdate = 0;
    float dt = bodies[0]->futurePositions.front().first;
    while (timeSinceUpdate >= dt) {
        for (auto& body : bodies) {
            body->futurePositions.pop_front();
        }

        timeSinceUpdate -= dt;
        stepsPerUpdate++;
        ApplyForces();
        dt = bodies[0]->futurePositions.front().first;
    }
}

void OrbitalMechanics::ApplyForces() {
    for (unsigned int ib = 0; ib < bodies.size(); ib++) {
        PhysicsBody& body = *bodies[ib];
        for (int io = 0; io < bodies.size(); io++) {
            if (io == ib) continue;

            PhysicsBody& other = *bodies[io];
            vec3 r = other.position - body.position;

            vec3 F = r.normalised()*(G*body.mass*other.mass/r.magnitudeSquared());
            body.ApplyInstantaneousForce(F);
            other.ApplyInstantaneousForce(F*-1.f);
        }
    }

    for (auto& body : bodies) {
        body->Update(dt);
    }
}

void OrbitalMechanics::AddBody(PhysicsBody& body) {
    bodies.push_back(&body);
}

void OrbitalMechanics::CalcFutureStates(int steps) {
    for (unsigned int is = 0; is < steps; is++) {
        ApplyForces();
    }
}

void OrbitalMechanics::DrawTrajectories() {
    for (const auto& body : bodies) {
        int nPositions = body->futurePositions.size();
        for (unsigned int is = 0; is < nPositions - 1; is++) {
            vec3 pos = body->futurePositions[is].second;
            vec3 nextPos = body->futurePositions[is+1].second;

            float alpha = 1.0f - exp(-(float)is/(0.1f*(float)nPositions));

            DrawLine3D({pos.x, pos.y, pos.z}, {nextPos.x, nextPos.y, nextPos.z}, Fade(WHITE, alpha));
        }
    }
}