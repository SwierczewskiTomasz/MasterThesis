import os
import numpy as np
from matplotlib import pyplot as plt
from matplotlib.patches import Circle
from matplotlib.collections import PatchCollection


# let's plot in the YZ plane, so setting x0 equal to some value
def createFigure(dir1, dir2, outputDir, nbins):

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

    fig, ax = plt.subplots(figsize=(10, 10), dpi=200)
    # p1 = ax.loglog(data_x, data_y1 - data_y2, label="Difference")
    # p2 = ax.loglog(data_x, data_y2, label = "Tomasz")
    p1 = ax.semilogx(data_x, data_y1, label = "DTFE_M")
    p2 = ax.semilogx(data_x, data_y2, label = "DTFE_T")
    # p1 = ax.loglog(data_x, data_y1, label = "DTFE_M")
    # p2 = ax.loglog(data_x, data_y2, label = "DTFE_T")
    # Tomasz - DTFE z Monte Carlo, 100 próbek na każdą komórkę siatki\nMarius - DTFE z Monte Carlo, 100 próbek na każdą komórkę siatki\n
    ax.set_title("1024Mpc, NGRID = 128, R = 5, NBINS = 1000, H0 = 1")
    ax.legend()
    plt.tight_layout()
    plt.savefig(outputDir)

# def plot_tetrahedron(ax, tetrahedron):
#     ax.plot3D(tetrahedron)
triangle_surface = {}

def plot_tetrahedron(fig, ax, points):
    ax.scatter(points[:, 0], points[:, 1], points[:, 2], color='b')
    p0 = (0.0, 0.0, 0.5)
    distance = np.array([(((points[i,0] - p0[0]) * (points[i,0] - p0[0]) + (points[i,1] - p0[1]) * (points[i,1] - p0[1]) + (points[i,2] - p0[2]) * (points[i,2] - p0[2]))/3)**(1/2) for i in range(4)])
    # points1 = np.array(points).T.reshape(-1, 1, 3)
    # print("points: ", points1)
    # segments = np.concatenate([points1[:], points1[:]], axis=1)
    # print("segments: ", segments)

    # LineCollection(segments, cmap='gray')
    # print("Distance: ", distance)
    for p1 in range(len(points)):
        for p2 in range(p1 + 1, len(points)):
            # myColor = (distance, distance, distance, 1)
            n = 10
            p_current = points[p1].copy()
            dist_current = distance[p1]
            p_inc = [0,0,0]
            for dim in range(3):
                p_inc[dim] = (points[p2, dim] - points[p1, dim])/n
            dist_inc = (distance[p2] - distance[p1])/n

            for i in range(n):
                p_next = p_current.copy()
                for dim in range(3):
                    p_next[dim] = p_next[dim] + p_inc[dim]

                dist_next = dist_current + dist_inc
                myColor = (dist_current, dist_current, dist_current, 1)
                ax.plot([p_current[0], p_next[0]], [p_current[1], p_next[1]], [p_current[2], p_next[2]], color=myColor, lw='1')
                dist_current = dist_next
                p_current = p_next.copy()



            
            # LineCollection(segments, cmap='gray')
            # ax.plot3D(points[[p1, p2], 0], points[[p1, p2], 1], points[[p1, p2], 2], color=myColor, lw='1', antialiased=True)
            # fig.colorbar(line, ax)
            for p3 in range(p2 + 1, len(points)):
                key = str(points[[p1, p2, p3], :])
                if not key in triangle_surface:
                    avgP = [0,0,0]
                    dist = 0
                    for dim in range(3):
                        avgP[dim] = (points[p1, dim] + points[p2, dim] + points[p1, dim])/3
                        dist += (avgP[dim] - p0[dim]) * (avgP[dim] - p0[dim])
                    dist = (dist / 3)**(1/2)
                    myColor = (dist, dist, dist)
                    ax.plot_trisurf(points[[p1, p2, p3], 0], points[[p1, p2, p3], 1], points[[p1, p2, p3], 2], linewidth=0.2, antialiased=True, 
                    alpha=0.05, color=myColor)
                    triangle_surface[key] = 1
    
    for point in points:
        ax.text(point[0], point[1], point[2] + 0.05, str(point))

def generate_triangles_3D():
    points = np.array([[0.1, 0.1, 0.1], [0.2, 0.2, 0.8], [0.3, 0.7, 0.7], [0.6, 0.4, 0.4]])
    triangles = [points]
    points = np.array([[0.8, 0.8, 0.8], [0.2, 0.2, 0.8], [0.3, 0.7, 0.7], [0.6, 0.4, 0.4]])
    triangles += [points]
    points = np.array([[0.8, 0.8, 0.8], [1.0, 1.0, 0.1], [0.3, 0.7, 0.7], [0.6, 0.4, 0.4]])
    triangles += [points]
    return triangles

def generate_triangles_2D_0():
    triangles = [[[0.1, 0.1], [0.8, 0.2], [0.2, 0.8]]]
    circles = [[0.4125, 0.4125]]
    radius = [0.441941738]
    triangles += [[[0.2, 0.8], [0.9, 0.9], [0.8, 0.2]]]
    circles += [[0.5875, 0.5875]]
    radius += [0.441941738]
    wstawiany = [2.0, 2.0]
    return triangles, circles, radius, wstawiany



def generate_triangles_2D_1():
    triangles  = [[[0.0, 0.0], [1.0, 0.0], [0.0, 1.0]]]
    circles =[[0.5, 0.5]]
    radius = [0.707106]
    triangles += [[[1.0, 1.0], [1.0, 0.0], [0.0, 1.0]]]
    circles += [[0.5, 0.5]]
    radius += [0.707106]
    wstawiany = [0.3, 0.3]
    return triangles, circles, radius, wstawiany

def generate_triangles_2D_2():
    triangles = [[[0.0, 0.0], [1.0, 0.0], [0.3, 0.3]]]
    circles = [[0.5, -0.2]]
    radius = [0.538516481]

    triangles += [[[0.0, 0.0], [0.3, 0.3], [0.0, 1.0]]]
    circles += [[-0.2, 0.5]]
    radius += [0.538516481]

    triangles += [[[1.0, 0.0], [0.3, 0.3], [1.0, 1.0]]]
    circles += [[0.8, 0.5]]
    radius += [0.538516481]

    triangles += [[[0.0, 1.0], [0.3, 0.3], [1.0, 1.0]]]
    circles += [[0.5, 0.8]]
    radius += [0.538516481]

    wstawiany = [0.7, 0.6]
    return triangles, circles, radius, wstawiany

def generate_triangles_2D_3():
    triangles = [[[0.0, 0.0], [1.0, 0.0], [0.3, 0.3]]]
    circles = [[0.5, -0.2]]
    radius = [0.538516481]

    triangles += [[[0.0, 0.0], [0.3, 0.3], [0.0, 1.0]]]
    circles += [[-0.2, 0.5]]
    radius += [0.538516481]

    triangles += [[[1.0, 0.0], [0.3, 0.3], [0.7, 0.6]]]
    # circles += [[0.677272727, 0.213636364]]
    circles += [[0.677, 0.213]]
    radius += [0.387031508]

    triangles += [[[1.0, 0.0], [1.0, 1.0], [0.7, 0.6]]]
    circles += [[1.25, 0.5]]
    radius += [0.559016994]

    triangles += [[[0.0, 1.0], [0.3, 0.3], [0.7, 0.6]]]
    # circles += [[0.301351351, 0.714864865]]
    circles += [[0.301, 0.714]]
    radius += [0.414867066]

    triangles += [[[0.0, 1.0], [1.0, 1.0], [0.7, 0.6]]]
    # circles += [[0.5, 1.0625]]
    circles += [[0.5, 1.062]]
    radius += [0.503891109]

    wstawiany = [0.45, 0.8]
    return triangles, circles, radius, wstawiany


def plot_triangulation_3D(outputPath):
    fig = plt.figure(figsize=(10,10),dpi=200)
    ax = plt.axes(projection='3d')
    ax.view_init(8, 300)
    triangles = generate_triangles_3D()
    plot_tetrahedron(fig, ax, triangles[0])
    plot_tetrahedron(fig, ax, triangles[1])
    plot_tetrahedron(fig, ax, triangles[2])
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_zlabel("z")
    ax.set_xlim(1, 0)
    ax.set_ylim(0, 1)
    ax.set_zlim(0, 1)
    plt.savefig(outputPath)

def plot_triangle(fig, ax, points):
    # ax.scatter(points[:, 0], points[:, 1], color='b')
    for p1 in range(len(points)):
        for p2 in range(p1 + 1, len(points)):
            ax.plot([points[p1][0], points[p2][0]], [points[p1][1], points[p2][1]], lw='1', color=(0, 0, 0))
    # for point in points:
    #     ax.text(point[0], point[1] + 0.05, str(point))

def plot_circle_2d(fig, ax, center, radius, myColor):
    circle = Circle((center[0], center[1]), radius, color=myColor, fill = False)
    ax.add_patch(circle)
    ax.scatter(center[0], center[1], color='r')
    if(center[0] <= 1.2):
        ax.text(center[0], center[1] + 0.02, str(center))
    else:
        ax.text(center[0] - 0.15, center[1] + 0.02, str(center))
    # patches = [circle]
    # p = PatchCollection(patches, alpha=0.4)
    # ax.add_collection(p)

def square_distance_between_points(point1, point2):
    result = 0
    for index in range(len(point1)):
        temp = point1[index] - point2[index]
        result += temp * temp
    return result

def plot_triangulation_2D(outputPath):
    fig, ax = plt.subplots(figsize=(10,10),dpi=200)

    triangles, circles, radius, wstawiany = generate_triangles_2D_3()
    
    plotted_triangles = {}
    plotted_points = {}
    plotted_circles = {}
    global_points = {"[0.0, 0.0]", "[0.0, 1.0]", "[1.0, 0.0]", "[1.0, 1.0]"}
    
    for triangle in triangles:
        if not str(triangle) in plotted_triangles:
            plotted_triangles[str(triangle)] = 1
            plot_triangle(fig, ax, triangle)
            for point in triangle:
                if not str(point) in global_points:
                    if not str(point) in plotted_points:
                        plotted_points[str(point)] = 1
                        ax.scatter(point[0], point[1], color='b')
                        ax.text(point[0] + 0.04, point[1] + 0.02, str(point))
                else:
                    if not str(point) in plotted_points:
                        plotted_points[str(point)] = 1
                        ax.scatter(point[0], point[1], color=(0, 0.6, 0))
                        ax.text(point[0] + 0.04, point[1] + 0.02, str(point))
    
    wewnatrz_kolor = (0.4, 0.4, 0.4)
    zewnatrz_kolor = (0.85, 0.85, 0.85)

    rysowac_okregi = True
    rysowac_wstawiany = True
    # rysowac_okregi = False
    # rysowac_wstawiany = False


    if rysowac_okregi:
        for c_index in range(len(circles)):
            if not (str(circles[c_index]) + str(radius[c_index])) in plotted_circles:
                plotted_circles[(str(circles[c_index]) + str(radius[c_index]))] = 1
                if square_distance_between_points(circles[c_index], wstawiany) <= radius[c_index] * radius[c_index]:
                    plot_circle_2d(fig, ax, circles[c_index], radius[c_index], wewnatrz_kolor)
                else:
                    plot_circle_2d(fig, ax, circles[c_index], radius[c_index], zewnatrz_kolor)
    

    if rysowac_wstawiany:
        ax.scatter(wstawiany[0], wstawiany[1], color=(0, 0, 0))
        ax.text(wstawiany[0] + 0.04, wstawiany[1] + 0.02, str(wstawiany))

    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_xlim(-0.25, 1.25)
    ax.set_ylim(-0.25, 1.25)
    fig.tight_layout()
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
outputPath = cwd + "/do_latexa/" + "2021_06_09_01.png"

NBINS = 1000

createFigure(path1, path2, outputPath, NBINS)
# plot_triangulation_2D(outputPath)
# przyklad_z_neta()

