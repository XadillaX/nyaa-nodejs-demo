#include "nbody.h"
using namespace std;

namespace __nbody__ {

static const double PI = 3.141592653589793;
static const double SOLAR_MASS = 4 * PI * PI;
static const double DAYS_PER_YEAR = 365.24;

Body::Body()
{
}

Body& Body::jupiter()
{
    static Body p;
    p.x = 4.84143144246472090e+00;
    p.y = -1.16032004402742839e+00;
    p.z = -1.03622044471123109e-01;
    p.vx = 1.66007664274403694e-03 * DAYS_PER_YEAR;
    p.vy = 7.69901118419740425e-03 * DAYS_PER_YEAR;
    p.vz = -6.90460016972063023e-05 * DAYS_PER_YEAR;
    p.mass = 9.54791938424326609e-04 * SOLAR_MASS;
    return p;
}

Body& Body::saturn()
{
    static Body p;
    p.x = 8.34336671824457987e+00;
    p.y = 4.12479856412430479e+00;
    p.z = -4.03523417114321381e-01;
    p.vx = -2.76742510726862411e-03 * DAYS_PER_YEAR;
    p.vy = 4.99852801234917238e-03 * DAYS_PER_YEAR;
    p.vz = 2.30417297573763929e-05 * DAYS_PER_YEAR;
    p.mass = 2.85885980666130812e-04 * SOLAR_MASS;
    return p;
}

Body& Body::uranus()
{
    static Body p;
    p.x = 1.28943695621391310e+01;
    p.y = -1.51111514016986312e+01;
    p.z = -2.23307578892655734e-01;
    p.vx = 2.96460137564761618e-03 * DAYS_PER_YEAR;
    p.vy = 2.37847173959480950e-03 * DAYS_PER_YEAR;
    p.vz = -2.96589568540237556e-05 * DAYS_PER_YEAR;
    p.mass = 4.36624404335156298e-05 * SOLAR_MASS;
    return p;
}

Body& Body::neptune()
{
    static Body p;
    p.x = 1.53796971148509165e+01;
    p.y = -2.59193146099879641e+01;
    p.z = 1.79258772950371181e-01;
    p.vx = 2.68067772490389322e-03 * DAYS_PER_YEAR;
    p.vy = 1.62824170038242295e-03 * DAYS_PER_YEAR;
    p.vz = -9.51592254519715870e-05 * DAYS_PER_YEAR;
    p.mass = 5.15138902046611451e-05 * SOLAR_MASS;
    return p;
}

Body& Body::sun()
{
    static Body p;
    p.mass = SOLAR_MASS;
    return p;
}

Body& Body::OffsetMomentum(double px, double py, double pz)
{
    vx = -px / SOLAR_MASS;
    vy = -py / SOLAR_MASS;
    vz = -pz / SOLAR_MASS;
    return *this;
}

NBodySystem::NBodySystem() :
        bodies { {
            Body::sun(),
            Body::jupiter(),
            Body::saturn(),
            Body::uranus(),
            Body::neptune()
        } }
{
    double px = 0.0;
    double py = 0.0;
    double pz = 0.0;
    for(unsigned i = 0; i < bodies.size(); ++i)
    {
        px += bodies[i].vx * bodies[i].mass;
        py += bodies[i].vy * bodies[i].mass;
        pz += bodies[i].vz * bodies[i].mass;
    }
    bodies[0].OffsetMomentum(px, py, pz);
}

void NBodySystem::advance(double dt)
{
    const unsigned N = (bodies.size() - 1) * bodies.size() / 2;
    struct __attribute__((aligned(16))) R {
        double dx, dy, dz, filler;
    };
    static R r[1000];
    static __attribute__((aligned(16))) double mag[1000];

    for(unsigned i = 0, k = 0; i < bodies.size() - 1; ++i)
    {
        Body& iBody = bodies[i];
        for(unsigned j = i + 1; j < bodies.size(); ++j, ++k)
        {
            r[k].dx = iBody.x - bodies[j].x;
            r[k].dy = iBody.y - bodies[j].y;
            r[k].dz = iBody.z - bodies[j].z;
        }
    }

    for(unsigned i = 0; i < N; i += 2)
    {
        __m128d dx, dy, dz;
        dx = _mm_loadl_pd(dx, &r[i].dx);
        dy = _mm_loadl_pd(dy, &r[i].dy);
        dz = _mm_loadl_pd(dz, &r[i].dz);

        dx = _mm_loadh_pd(dx, &r[i+1].dx);
        dy = _mm_loadh_pd(dy, &r[i+1].dy);
        dz = _mm_loadh_pd(dz, &r[i+1].dz);

        __m128d dSquared = dx * dx + dy * dy + dz * dz;

        __m128d distance = _mm_cvtps_pd(_mm_rsqrt_ps(_mm_cvtpd_ps(dSquared)));
        for(unsigned j = 0; j < 2; ++j)
        {
            distance = distance * _mm_set1_pd(1.5) - 
                    ((_mm_set1_pd(0.5) * dSquared) * distance) *
                    (distance * distance);
        }

        __m128d dmag = _mm_set1_pd(dt)/(dSquared) * distance;
        _mm_store_pd(&mag[i],dmag);
    }

    for(unsigned i=0,k=0; i < bodies.size()-1; ++i)
    {
        Body& iBody = bodies[i];
        for(unsigned j = i + 1; j < bodies.size(); ++j, ++k)
        {
            iBody.vx -= r[k].dx * bodies[j].mass * mag[k];
            iBody.vy -= r[k].dy * bodies[j].mass * mag[k];
            iBody.vz -= r[k].dz * bodies[j].mass * mag[k];

            bodies[j].vx += r[k].dx * iBody.mass * mag[k];
            bodies[j].vy += r[k].dy * iBody.mass * mag[k];
            bodies[j].vz += r[k].dz * iBody.mass * mag[k];
        }
    }

    for (unsigned i = 0; i < bodies.size(); ++i)
    {
        bodies[i].x += dt * bodies[i].vx;
        bodies[i].y += dt * bodies[i].vy;
        bodies[i].z += dt * bodies[i].vz;
    }
}

double NBodySystem::energy()
{
    double e = 0.0;

    for(unsigned i = 0; i < bodies.size(); ++i)
    {
        Body const & iBody = bodies[i];
        double dx, dy, dz, distance;
        e += 0.5 * iBody.mass *
                (iBody.vx * iBody.vx +
                iBody.vy * iBody.vy +
                iBody.vz * iBody.vz);

        for(unsigned j = i + 1; j < bodies.size(); ++j)
        {
            Body const & jBody = bodies[j];
            dx = iBody.x - jBody.x;
            dy = iBody.y - jBody.y;
            dz = iBody.z - jBody.z;

            distance = sqrt(dx*dx + dy*dy + dz*dz);
            e -= (iBody.mass * jBody.mass) / distance;
        }
    }

    return e;
}

}
