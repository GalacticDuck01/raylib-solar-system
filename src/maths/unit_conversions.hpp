#pragma once

#include "maths/constants.hpp"

// --------------------------------------------------
// Time
// --------------------------------------------------

#define SECONDS_TO_MILLISECONDS 1e3f
#define MILLISECONDS_TO_SECONDS 1e-3f
#define SECONDS_TO_MICROSECONDS 1e6f
#define MICROSECONDS_TO_SECONDS 1e-6f
#define SECONDS_TO_NANOSECONDS  1e9f
#define NANOSECONDS_TO_SECONDS  1e-9f

// --------------------------------------------------
// Length
// --------------------------------------------------

#define METRES_TO_KILOMETRES  1e-3f
#define KILOMETRES_TO_METRES  1e3f
#define METRES_TO_CENTIMETRES 1e2f
#define CENTIMETRES_TO_METRES 1e-2f

// --------------------------------------------------
// Angles
// --------------------------------------------------

#define DEG_TO_RAD PI/180.0f
#define RAD_TO_DEG 180.0f/PI