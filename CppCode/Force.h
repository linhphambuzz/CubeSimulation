#ifndef FORCE_H
#define FORCE_H
#include "Particles.h"

class Force: public Particles
{
    public:
        Force();
        float get_force(int pos1,int pos2);
        float* force_val(int pos);
        void process_particles(int pos);

};

#endif // FORCE_H
