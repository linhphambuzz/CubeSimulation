#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np 
import random

#define constant 
center_mass= 50000.0 
g=9.98 
mass=10.0 # mass of each particle 
max_particles= 500 
max_size=2000
max_v= 5.0 
time_steps=1000 


# In[2]:


#2 matrix for particles and updates 
particles=np.zeros((max_particles+1,7),dtype=float) 
updates=np.zeros((max_particles+1,7),dtype=float) 


# In[3]:


#set center of mass , set first column all to mass
particles[:,0]=updates[:,0]= mass
particles[0,0]= updates[0,0]= center_mass
particles[0,1:6]=0 


# In[4]:


def pos_neg():
    a=random.random() 
    if a>0.5:
        return -1
    return 1


# In[5]:


#func to generate random particle and initiate v, r 
def generate_particle(pos):
    x0=(random.random())*max_size/2  #position in the range of the cube size max_radius 
    y0=(random.random())*max_size/2 
    z0=(random.random())*max_size/2 
    #make coordinate randomly postive/negative 
    particles[pos,1]=x=x0*pos_neg()
    particles[pos,2]=y=y0*pos_neg()
    particles[pos,3]=z=z0*pos_neg()
    #calculate distance r
    r=np.sqrt(x**2+y**2+z**2)
    #calculate intit v interacting with CM 
    v=np.sqrt(g*center_mass/r) 
    particles[pos,4]=vx=v*(x/r)
    particles[pos,5]=vy=v*(y/r)
    particles[pos,6]=vz=v*(z/r)
    


# In[6]:


#func to calculate distance bw 2 particle 
def distance(pos1,pos2): 
    r=0 
    for i in range(1,4):
        di= particles[pos1,i]-particles[pos2,i]
        r+=di**2
    return np.sqrt(r)
     


# In[7]:


#function to calculate force bw 2 particles 
def get_force(pos1,pos2): 
    d= distance(pos1,pos2)
    return (g*particles[pos1,0]*particles[pos2,0])/d**2


# In[8]:


#force exert on 1 particle 
def force(pos): 
    f=np.zeros(4)
    f[0]=0.0 #total force 
    f[1]=0.0 #fx
    f[2]=0.0 #fy
    f[3]=0.0 #fz
    for i in range(max_particles+1):
        while i!= pos: 
            f[0]+=get_force(pos,i)  #total force 
            f[1]+=f[0]*(particles[pos,1]- particles[i,1])/distance(pos,i)  #force in the x direction 
            f[2]+=f[0]*(particles[pos,2]- particles[i,2])/distance(pos,i) #force in the y direction 
            f[3]+=f[0]*(particles[pos,3]- particles[i,3])/distance(pos,i) #force in the z direction 
    return f
    


# In[9]:


#function to process particle 
def process_particle(pos): 
    #calculate acceleration a=F/m
    ax=force(pos)[1]/particles[pos,0] 
    ay=force(pos)[2]/particles[pos,0]
    az=force(pos)[3]/particles[pos,0]
    
    #calculate and update v
    vx=particles[pos,4]+ax
    vy=particle[pos,5]+ay
    vz=particle[pos,6]+az
    updates[pos,4]=vx
    updates[pos,5]=vy
    updates[pos,6]=vz
    
    #calculate and update x,y,z 
    updates[pos,1]=particles[pos,1] + vx
    updates[pos,2]=particles[pos,2] + vy 
    updates[pos,3]=particles[pos,3] + vz 
       


# In[10]:


#function to update particle matrix 
def update_particles():
    particles=updates 


# In[11]:


#function to write vtk 
def save_vtk(i): 
        fname='data{:04d}.vtk'.format(i)
        fout=open(fname,'w')
        fout.write('# vtk DataFile\n')
        fout.write('Galaxy step {:04d}\nASCII\n\n'.format(i))
        fout.write('DATASET POLYDATA\nPOINTS {:03d} FLOAT\n'.format(max_particles+1))
        for j in range (max_particles+1): 
            fout.write('{:3.3f} {:3.3f} {:3.3f}\n'.format(particles[j,1],particles[j,2],particles[j,3]))
        fout.close()


# In[12]:


#generate data, save as the first file 
for i in range(1,max_particles+1): 
    generate_particle(i)
save_vtk(0)   


# In[ ]:


#main function calls 
for i in range(1,10): 
    for j in range(max_particles+1): 
        process_particle(j)
    update_particles()
    save_vtk(i)
    


# In[ ]:




