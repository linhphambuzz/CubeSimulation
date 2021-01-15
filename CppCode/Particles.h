#ifndef PARTICLES_H
#define PARTICLES_H


class Particles
{
    public:
        Particles();
        const float center_mass = 50000.0 ;
        const float g=9.81 ;
        const float mass=10.0;
        const static int max_particles = 500;
        const static int max_size = 2000; //size of the cube
        const static int max_step = 100; //the simulation will last 1000 secs
        //2D array with the column store the following data: mass, x,y,z,vx,vy,vz
        static float particles[max_particles+1][7];
        //2D array to update particle after interacting with other particles
        static float updates[max_particles+1][7];
        float distance(int pos1, int pos2); //function to calculate the distance between 2 particles
        void update(); //function to update the position of particles after interacting with other particles
        void save_vtk(int file); //function to write to file







};

#endif // PARTICLES_H
