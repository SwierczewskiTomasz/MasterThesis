import os
import numpy as np
from matplotlib import colors, cm, pyplot as plt
from mpl_toolkits import mplot3d
from matplotlib.colors import LogNorm
from matplotlib.ticker import LogFormatterExponent
from matplotlib.ticker import LogFormatter 
from matplotlib.ticker import LogLocator


def createFigure(dir1, dir2, outputDir, nbins):  # let's plot in the YZ plane, so setting x0 equal to some value

    data_x = np.loadtxt(dir1,
                        skiprows=2,
                        max_rows=nbins,
                        usecols=(0)
                        )

    data_y1 = np.loadtxt(dir1,
                         skiprows=2,
                         max_rows=nbins,
                         usecols=(3)
                         )

    data_y2 = np.loadtxt(dir2,
                         skiprows=2,
                         max_rows=nbins,
                         usecols=(3)
                         )                     

    fig, ax = plt.subplots(figsize=(10,10),dpi=200)
    p1 = ax.loglog(data_x, data_y1 - data_y2, label = "Difference")
    # p2 = ax.loglog(data_x, data_y2, label = "Tomasz")
    # p1 = ax.semilogx(data_x, data_y1, label = "Marius")
    # p2 = ax.semilogx(data_x, data_y2, label = "Tomasz")
    ax.set_title("Tomasz - DTFE using Monte Carlo, 100 subsamples in one grid cell\nMarius - DTFE using Monte Carlo, 100 subsamples in one grid cell\n1024Mpc, NGRID = 128, R = 5, NBINS = 1000, H0 = 1")
    ax.legend()
    plt.savefig(outputDir)

# def plot_tetrahedron(ax, tetrahedron):
#     ax.plot3D(tetrahedron)

def plot_tetrahedron(ax, points):
    ax.scatter(points[:,0], points[:,1], points[:,2], color='b')
    for pointIndex in range(len(points)):
        for secondPointIndex in range(pointIndex + 1, len(points)):
            ax.plot3D(points[[pointIndex, secondPointIndex], 0], points[[pointIndex, secondPointIndex], 1], points[[pointIndex, secondPointIndex], 2], color='g', lw='1')
            for thirdPointIndex in range(secondPointIndex + 1, len(points)):
                ax.plot_trisurf(points[[pointIndex, secondPointIndex, thirdPointIndex], 0], points[[pointIndex, secondPointIndex, thirdPointIndex], 1], points[[pointIndex, secondPointIndex, thirdPointIndex], 2], linewidth=0.2, antialiased=True, 
                alpha=0.1)
    
    for point in points:
        ax.text(point[0], point[1], point[2] + 0.05, str(point))

def generate_triangles():
    points = np.array([[0.1, 0.1, 0.1], [0.2, 0.2, 0.8], [0.3, 0.7, 0.7], [0.6, 0.4, 0.4]])
    triangles = [points]
    points = np.array([[0.8, 0.8, 0.8], [0.2, 0.2, 0.8], [0.3, 0.7, 0.7], [0.6, 0.4, 0.4]])
    triangles += [points]
    return triangles

def plot_triangulation(outputPath):
    fig = plt.figure(figsize=(10,10),dpi=200)
    ax = plt.axes(projection='3d')
    triangles = generate_triangles()
    plot_tetrahedron(ax, triangles[0])
    plot_tetrahedron(ax, triangles[1])
    ax.set_xlim(0, 1)
    ax.set_ylim(0, 1)
    ax.set_zlim(0, 1)
    plt.savefig(outputPath)

cwd = os.getcwd()
dir1 = "PDF1000-DTFE-128-top-hat-R5.00-DTFE_128_bin_2021_05_14.a_den.a_den"
# dir1 = "PDF1000-DTFE-256-top-hat-R5.00-DTFE_256_bin_2021_05_13.a_den.a_den"
# dir1 = "PDF1000-DTFE-256-top-hat-R5.00-DTFE_256_bin_2021_05_13_2.a_den.a_den"


dir2 = "PDF1000-DTFE-128-top-hat-R5.00-DTFE_test_2_2021_05_14_128_2.a_den"
# dir2 = "PDF1000-DTFE-256-top-hat-R5.00-DTFE_test_2_2021_05_14_256_1.a_den"
# dir2 = "PDF1000-DTFE-256-top-hat-R5.00-DTFE_test_2_2021_05_13_256_1.a_den"
# dir2 = "PDF1000-DTFE-256-top-hat-R5.00-DTFE_test_2_2021_04_27_256_1.a_den"

path1 = cwd + "/" + dir1
path2 = cwd + "/" + dir2
# outputPath = cwd + "/" + "DTFE_loglog_128_2.png"
outputPath = cwd + "/" + "Triangulation_2021_05_15_1.png"

NBINS = 1000

# createFigure(path1, path2, outputPath, NBINS)
plot_triangulation(outputPath)
