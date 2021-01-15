#include "Force.h"
#include "math.h"
#include<iostream>

Force::Force(){}
//calculate force between 2 particles
float Force::get_force(int pos1,int pos2)
{
    Particles obj;
    float d,f; //for distance,0 force
    d= obj.distance(pos1,pos2);
    f= (obj.g* obj.particles[pos1][0]* obj.particles[pos2][0])/ pow(d,2);
    return f;
}
//get total force exert on one particle
float* Force::force_val(int pos)
{
    Force obj;
    float* force_arr;
    float f[4]={0.0,0.0,0.0,0.0};
    force_arr=f;
    for (int i=0;i<=obj.max_particles;i++){
        while(i!=pos){
            f[0]+=obj.get_force(i,pos);
            f[1]+=force_arr[0]*(obj.particles[pos][1]-obj.particles[i][1])/obj.distance(pos,i);
            f[2]+=force_arr[0]*(obj.particles[pos][2]-obj.particles[i][2])/obj.distance(pos,i);
            f[3]+=force_arr[0]*(obj.particles[pos][3]-obj.particles[i][3])/obj.distance(pos,i);
        }
    }
    return force_arr;
}
//function to get acceleration, calculate new v...
void Force::process_particles(int pos)
{
    float ax,ay,az;//acceleration
    float vx,vy,vz; //velocity
    Force obj;  //object of type Force.
    ax= obj.force_val(pos)[1]/obj.particles[pos][0];   //   a=F/m
    ay= obj.force_val(pos)[2]/obj.particles[pos][0];
    az= obj.force_val(pos)[3]/obj.particles[pos][0];
    //calcuate velocity
    obj.updates[pos][4]=vx= obj.particles[pos][4] + ax;
    obj.updates[pos][5]=vy= obj.particles[pos][5] + ay;
    obj.updates[pos][6]=vz= obj.particles[pos][6] + az;
    //update x,y,z
    obj.updates[pos][1]=obj.particles[pos][1] + vx;
    obj.updates[pos][2]=obj.particles[pos][2] + vy;
    obj.updates[pos][3]=obj.particles[pos][3] + vz;

}


