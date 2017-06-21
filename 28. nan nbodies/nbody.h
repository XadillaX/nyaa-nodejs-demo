#ifndef __NBODY_H__
#define __NBODY_H__

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <tr1/array>
#include <immintrin.h>

namespace __nbody__ {

class Body {
public:
    double x;
    double y;
    double z;
    double filler;
    double vx;
    double vy;
    double vz;
    double mass;

public:
    Body();
    static Body& jupiter();
    static Body& saturn();
    static Body& uranus();
    static Body& neptune();
    static Body& sun();
    
    Body& OffsetMomentum(double px, double py, double pz);
};

class NBodySystem {
public:
    NBodySystem();

    void advance(double dt);
    double energy();

private:
    std::tr1::array<Body, 5> bodies;
};

}

#endif
