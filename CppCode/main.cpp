#include <iostream>
#include "Particles.h"
#include "Force.h"
#include<cstdlib>
#include<ctime>
#include <math.h>


using namespace std;

int main()
{
    Force obj;

    //generate first set of random particles
    float x0, y0, z0,x,y,z;
    float arr[3];
    float v;
    double r;
    srand((unsigned) time(0));
    for(int i=1;i<=obj.max_particles;i++){

        for (int i=0;i<3;i++){
        arr[i]=rand()% ((obj.max_size)/2) ;
        if(rand()%2==0) arr[i]*=-1;
        }
        x=obj.particles[i][1]=x0=arr[0];
        y=obj.particles[i][2]=y0=arr[1];
        z=obj.particles[i][3]=z0=arr[2];

        //calculate distance r
        r=sqrt(pow(x,2)+pow(y,2)+pow(z,2));
        //calculate initial v
        v=sqrt(obj.g*obj.center_mass/r) ;
        // Assign vector component
        obj.particles[i][4]= v*(x/r);
        obj.particles[i][5]= v*(y/r);
        obj.particles[i][6]= v*(z/r);



    }
    //save the first file
    obj.save_vtk(0);
    //create all the file
    for(int t=1; t<=obj.max_step;t++){
        for(int j=0;j<=obj.max_particles;j++){
            obj.process_particles(j);
        }
        obj.update();
        obj.save_vtk(t);


    }







    return 0;
}
