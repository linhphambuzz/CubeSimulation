#include "Particles.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

float Particles::particles[max_particles+1][7];
float Particles::updates[max_particles+1][7];

Particles::Particles()
{
    for(int i=0;i<=max_particles;i++)
    {
        particles[i][0]=updates[i][0]=mass;
    }
    //set CM
    particles[0][0]=center_mass;
    //set CM's property
    for (int i=1;i<7;i++){
        particles[0][i]=0;
    }

}
//function to calculate the distance between 2 particles
float Particles::distance(int pos1, int pos2)
{
    float r=0.0;
    float di;
    for (int i=1;i<4;i++){
        di=particles[pos1][i] - particles[pos2][i] ;
        r+=pow(di,2) ;
    }
    return sqrt(r);
}
//function to update the position of particles after interacting with other particles
void Particles::update(){
    for(int i=0; i<=max_particles;i++){
        for(int j=0;j<=6;j++){
            particles[i][j]=updates[i][j];
        }
    }
}

//save data to be read in paraview
void Particles::save_vtk(int file){
    string name = "data" + std::to_string(file) + ".vtk";
    ofstream MyFile(name);
    MyFile << "vtk data file \n" ;
    MyFile << "Galaxy step " + std::to_string(file) + "\n" ;
    MyFile << "ASCII \n" ;
    MyFile << "DATASET POLYDATA \n";
    MyFile << "POINT " + std::to_string(max_particles+1) + " FLOAT \n" ;

    for (int j=0;j<max_particles+1;j++){
        MyFile << std::to_string(particles[j][1])+ " " + std::to_string(particles[j][2]) + " " + std::to_string(particles[j][3]) + "\n" ;
    }
    MyFile.close();

}



