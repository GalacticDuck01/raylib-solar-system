#include "OrbitalMechanics.hpp"

#include <raymath.h>
#include <math.h>

void OrbitalMechanics::RenderUpdate(double deltaTime) {
    accumulatedTime += GetFrameTime();
    stepsThisRenderCall = 0;

    if (bodies.size() == 0) return;

    while (!bodies[0]->futurePositions.empty()) {
        double dt = bodies[0]->futurePositions.front().first;

        if (accumulatedTime < dt) break;

        for (auto& body : bodies) {
            body->futurePositions.pop_front();
        }

        accumulatedTime -= dt;
        stepsThisRenderCall++;
    }

    if (stepsThisRenderCall != 0) CalcFutureStates(stepsThisRenderCall);
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
            other.ApplyInstantaneousForce(F*-1.);
        }
    }
}

void OrbitalMechanics::AddBody(PhysicsBody& body) {
    bodies.push_back(&body);
}

void OrbitalMechanics::CalcFutureStates(int steps) {
    for (unsigned int is = 0; is < steps; is++) {
        ApplyForces();
        bodies[0]->DetermineStepSize(dt);

        for (auto& body : bodies) {
            body->Update(dt);
        }

        dt *= 2.;
    }
}

void OrbitalMechanics::DrawTrajectories(int nLines) {
    for (const auto& body : bodies) {
        int nPositions = body->futurePositions.size();
        int dp = nPositions > nLines ? nPositions/nLines : 1;
        for (unsigned int is = 0; is < nPositions - dp; is += dp) {
            vec3 pos = body->futurePositions[is].second;
            vec3 nextPos = body->futurePositions[is+dp].second;

            double alpha = 1.0f - exp(-(double)is/(0.1f*(double)nPositions));

            DrawLine3D({(float)pos.x, (float)pos.y, (float)pos.z}, {(float)nextPos.x, (float)nextPos.y, (float)nextPos.z}, Fade(WHITE, alpha));
        }
    }
}