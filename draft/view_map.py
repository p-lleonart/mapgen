import matplotlib.pyplot as plt
import numpy as np
from os.path import dirname

def read_map(filepath) -> np.ndarray:
    with open(filepath, 'r') as f:
        data = f.readlines()
        map = np.ndarray((int(data[0].split(" ")[1]), int(data[0].split(" ")[0])))

        for i in range(1, len(data)):
            j = 0
            for el in data[i].split(" "):
                if el != "|" and el != "|\n":
                    map[i-1][j-1] = float(el)
                j+=1
        return map

def main():
    Z = read_map(dirname(dirname(__file__)) + "/maps/map.txt")
    X = np.linspace(0, Z.shape[1], Z.shape[1])
    Y = np.linspace(0, Z.shape[0], Z.shape[0])

    X, Y = np.meshgrid(X, Y)
    ax = plt.figure().add_subplot(projection='3d')
    ax.plot_surface(X, Y, Z, cmap=plt.cm.coolwarm)
    plt.show()

    A = read_map(dirname(dirname(__file__)) + "/maps/map_smooth.txt")
    ax = plt.figure().add_subplot(projection='3d')
    ax.plot_surface(X, Y, A, cmap=plt.cm.coolwarm)
    plt.show()

if __name__ == "__main__":
    main()
