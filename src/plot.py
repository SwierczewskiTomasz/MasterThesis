#!/usr/bin/env python
# coding: utf-8
# In[1]:


import numpy as np
from matplotlib import colors, cm, pyplot as plt
import os
from matplotlib.colors import LogNorm

#plt.ioff()

# cwd = os.getcwd() #get the current working directory
# name_den= "fields.a_den"#the name of the density file interpolated on a grid
# name_vel= "fields.a_vel"#the name of the velocity file interpolated on a grid 
# name_veldiv="fields.a_velDiv" #the name of the velocity divergence file interpolated on a grid 
# path_den=cwd+"/"+name_den
# path_vel=cwd+"/"+name_vel
# path_veldiv=cwd+"/"+name_veldiv
path_den_my="../wyniki2/DTFE_test_2021_04_14_256_MC.a_den"
path_den_def="../wyniki2/DTFE_test_2021_04_14_256.a_den"
path_den="../data/Topolski/test_dtfe256.a_den"
path_den_dtfe="../data/DTFE_wyniki/DTFE_256.a_den"
path_den_04_22="../wyniki/DTFE_test_2_2021_04_22_128.a_den"

grid_points=128
L=200

#caution! in the interpolated files, the coordinate values start from 2, end at 1022 
#and the increment is equal to 4
#this is due to the grid options chosen in DTFE, namely, what was used was: --grid 256, 
#therefore the increment is L=1024 / 256 = 4 

#assuming that data_den/data_ is N lines of text, where in each line the order is:
# x y z density_at_(x,y,z)     or
# x y z vel_X_at(x,y,z) vel_Y_at(x,y,z) vel_Z_at(x,y,z)

#z0 mod 4 must be equal 2 
    
#the grid incides go from 0 to 127, so just start consecutively picking the lines after the 
#x0_grid*128*128 th one until (x0_grid +1)*128*128 + 1!
#then reshape the array and we have a 2D array of size 128x128  - given slice (at z0_grid)
#ready to be plotted via matshow 

#in the fldssmooth interpolated fields, only a range: 0.05*L to 0.95*L was taken in each direction
#with no --periodic option supplemented accordingly
#therefore, the range of the plot in h^{-1}Mpc is from 51,2 Mpc/h to 972.8


def plot_2D_density_contrast_grid(datafile,x0_grid): #let's plot in the YZ plane, so setting x0 equal to some value
    density=np.loadtxt(datafile,
                       skiprows=x0_grid*grid_points*grid_points,
                       max_rows=grid_points*grid_points,
                       usecols=(0)#usecols=(3)
                      ).reshape(grid_points,grid_points)
    dens_avg=np.mean(density)
    dens_contrast= density/dens_avg - 1*np.ones(density.shape)

    fig, ax = plt.subplots(figsize=(40,40),dpi=200)
    cs = ax.imshow(dens_contrast+1,
                   cmap='seismic',
                   norm=LogNorm(),
                   interpolation='gaussian')
    cbar = fig.colorbar(cs)
    fig.suptitle(r'Density contrast (logscale)'+'\n'+ r'$\delta(\mathbf{x})+1= \frac{\rho(\mathbf{x})}{\rho_{0}}$',fontsize=50)
    cbar.ax.tick_params(labelsize=60)
    #the grid indices ('x') are from 0 to 511 (1-512)
    #the original tesselation ('y') was from 51,2Mpc/h to 972.8
    #we translate the desired xticks: 100, 200, ..., 900
    #into the language of grid indices via:  x = (y-51,2)/1.8
    #while leaving the original labels
    phys_dist_display_min=0
    phys_dist_display_max=199
    y=np.linspace(phys_dist_display_min,phys_dist_display_max,num=10) #the physical distances to be displayed
    x=y*grid_points/L                                             #the actual location of the ticks on the grid
    #x=(y-51.2*np.ones(9))/1.8
    
    ax.set_xticks(x)
    ax.set_yticks(x)
    ax.set_xticklabels(np.asarray(y,dtype=int))
    ax.set_yticklabels(np.asarray(y,dtype=int))
    ax.set_ylabel(r'Distance [$h^{-1}$ Mpc]')
    ax.set_xlabel(r'Distance [$h^{-1}$ Mpc]')
    ax.xaxis.label.set_size(35)
    ax.yaxis.label.set_size(35)
    ax.tick_params(axis='both', which='major', labelsize=30)
    ax.tick_params(axis='both', which='minor', labelsize=30)
    plt.savefig("picdensctrg"+str(x0_grid)+".png")
    
def plot_2D_density_grid(datafile,x0_grid,string): #let's plot in the YZ plane, so setting x0 equal to some value
    density=np.loadtxt(datafile,
                       skiprows=x0_grid*grid_points*grid_points,
                       max_rows=grid_points*grid_points,
                       usecols=(0)#usecols=(3)
                      ).reshape(grid_points,grid_points)
    # dens_max = 112
    # dens_min=np.amin(density)
    # dens_avg = 1
    dens_max=np.amax(density)
    dens_min=np.amin(density)
    dens_avg=np.average(density)

    fig, ax = plt.subplots(figsize=(40,40),dpi=200)
    cs = ax.imshow(density,
                   cmap='viridis',
                   norm=LogNorm(vmin=0.12, vmax = 200), #LogNorm(vmin=0.008, vmax=112),
                   interpolation='gaussian')
    cbar = fig.colorbar(cs)
    fig.suptitle(r'Density $\rho(\mathbf{x})$ (logscale)',fontsize=50)
    cbar.ax.tick_params(labelsize=60)
    
    phys_dist_display_min=0
    phys_dist_display_max=199
    y=np.linspace(phys_dist_display_min,phys_dist_display_max,num=9) #the physical distances to be displayed
    x=y*grid_points/L                                             #the actual location of the ticks on the grid
    #x=(y-51.2*np.ones(9))/1.8
    ax.set_xticks(x)
    ax.set_yticks(x)
    ax.set_xticklabels(np.asarray(y,dtype=int))
    ax.set_yticklabels(np.asarray(y,dtype=int))
    ax.set_ylabel(r'Distance [$h^{-1}$ Mpc]')
    ax.set_xlabel(r'Distance [$h^{-1}$ Mpc]')
    ax.xaxis.label.set_size(35)
    ax.yaxis.label.set_size(35)
    ax.tick_params(axis='both', which='major', labelsize=30)
    ax.tick_params(axis='both', which='minor', labelsize=30)
    plt.savefig("out/plots/"+string+"/picdensg"+str(x0_grid)+"_"+string+".png")
    
def plot_2D_velocitydiv_grid(datafile,x0_grid): #let's plot in the YZ plane, so setting x0 equal to some value
    veldiv=np.loadtxt(datafile,
                       skiprows=x0_grid*grid_points*grid_points,
                       max_rows=grid_points*grid_points,
                       usecols=(0)).reshape(grid_points,grid_points)
    fig, ax = plt.subplots(figsize=(40,40),dpi=200)
    veldivmin=np.min(veldiv)
    veldivmax=np.max(veldiv)

    cs = ax.imshow(veldiv,vmin=veldivmin,vmax=veldivmax,
                   cmap='viridis',
                   interpolation='gaussian')
    cbar = fig.colorbar(cs)
    fig.suptitle(r'Velocity divergence $\nabla \cdot \mathbf{v}$ ',fontsize=50)
    cbar.ax.tick_params(labelsize=60)
    
    phys_dist_display_min=0
    phys_dist_display_max=199
    y=np.linspace(phys_dist_display_min,phys_dist_display_max,num=9) #the physical distances to be displayed
    x=y*grid_points/L #the actual location of the ticks on the grid
    ax.set_xticks(x)
    ax.set_yticks(x)
    ax.set_xticklabels(np.asarray(y,dtype=int))
    ax.set_yticklabels(np.asarray(y,dtype=int))
    ax.set_ylabel(r'Distance [$h^{-1}$ Mpc]')
    ax.set_xlabel(r'Distance [$h^{-1}$ Mpc]')
    ax.xaxis.label.set_size(35)
    ax.yaxis.label.set_size(35)
    ax.tick_params(axis='both', which='major', labelsize=30)
    ax.tick_params(axis='both', which='minor', labelsize=30)
    plt.savefig("picveldiv"+str(x0_grid)+".png")    
    
def plot_2D_velocity_grid(datafile,x0_grid):
    velocity=np.loadtxt(datafile,
                       skiprows=x0_grid*grid_points*grid_points,
                       max_rows=grid_points*grid_points,
                       usecols=(1,2) #taking the y,z velocitycomponents 
                      ).reshape(grid_points,grid_points,2)
    fig, ax = plt.subplots(figsize=(40,40),dpi=200)
    
    #this is one wants sparser placement of arrows
    divide=6 #for clearer illustration purposes, take every fnth points
    length=L*divide
    
    X=np.arange(0,grid_points/divide)
    Y=np.arange(0,grid_points/divide)
    
    
    U=velocity[0:-1:divide,0:-1:divide,0]
    V=velocity[0:-1:divide,0:-1:divide,1]
    
    
    #U=velocity[:,:,0]
    #V=velocity[:,:,1]

    M=np.hypot(U,V)
    cs = ax.quiver(X,Y,U,V,M,units='xy', pivot='tail', width=0.15,cmap='plasma')
    cbar = fig.colorbar(cs)
    fig.suptitle(r'Velocity field $\mathbf{v}(\mathbf{x})$'+' '+r'$[\frac{km}{s}]$ ',fontsize=50)
    cbar.ax.tick_params(labelsize=60)
    
    phys_dist_display_min=0
    phys_dist_display_max=199
    y=np.linspace(phys_dist_display_min,phys_dist_display_max,num=9) #the physical distances to be displayed
    x=y*grid_points/length #the actual location of the ticks on the grid
    ax.set_xticks(x)
    ax.set_yticks(x)
    ax.set_xticklabels(np.asarray(y,dtype=int))
    ax.set_yticklabels(np.asarray(y,dtype=int))
    ax.set_ylabel(r'Distance [$h^{-1}$ Mpc]')
    ax.set_xlabel(r'Distance [$h^{-1}$ Mpc]')
    ax.xaxis.label.set_size(35)
    ax.yaxis.label.set_size(35)
    ax.tick_params(axis='both', which='major', labelsize=30)
    ax.tick_params(axis='both', which='minor', labelsize=30)
    plt.savefig("picvelcoarser"+str(x0_grid)+".png")


# plot_2D_density_grid(path_den_my,126)

# for i in range(138, 256):
#     plot_2D_density_grid(path_den_def,i,"DEF")

# for i in range(10, 256):
#     plot_2D_density_grid(path_den_dtfe,i,"DTFE_2")

# plot_2D_density_grid(path_den_my,10,"MC_2")
# plot_2D_density_grid(path_den_dtfe,10,"DTFE_2")
plot_2D_density_grid(path_den_04_22,5,"04_22")

# plot_2D_density_contrast_grid(path_den,126)
# plot_2D_density_grid(path_den,126)
#plot_2D_velocity_grid(path_vel,126)
#plot_2D_velocity_grid(path_vel,126)
#plot_2D_velocitydiv_grid(path_veldiv,240)


# In[ ]: