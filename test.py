import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from scipy.spatial import ConvexHull


def read_points():
    file = open("hard_example.txt", "r")
    lines = file.read().split('\n')[:-1]
    file.close()
    result = []
    for line in lines[1:]:
        point = line.split('\t')[:3]
        point = [float(number) for number in point]
        result.append(point)
    return result


if __name__ == "__main__":
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    points = read_points()
    points = np.array(points)

    hull = ConvexHull(points)
    print('volume inside points is: ', hull.volume)

    for i in hull.simplices:
        plt.plot(points[i,0], points[i,1], points[i,2], 'r-')

    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')

    plt.show()
