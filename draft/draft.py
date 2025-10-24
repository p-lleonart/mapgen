import matplotlib.pyplot as plt
import numpy as np

import random as rd

def f(x, y):
    # return np.sin(1/2 * x**2 - 1/4 * y**2 + 3) * np.cos(2*x + 1 - np.exp(y))
    # np.sin(1/2 * x**2 - 1/4 * y**2 + 3) * np.cos(2*x + 1 - y)
    # np.sin(x**2 - y**2 + 1) * np.cos(- x + y -3)
    # np.sin(x**3 - y**2 + 1) * np.cos(- x + y -3)
    # np.sin(x**2 - y**3 + 1) * np.cos(- x + y -3)
    # x**4 - y**2 + 1
    # B = - x**3 + y - 3
    A = x**2 - y**2 + 1
    B = - x**3 + y - 3 # degB ne doit pas etre pair?
    return np.sin(A) * np.cos(B)

def gen(X: np.ndarray, Y: np.ndarray) -> np.ndarray:
    L = np.zeros((len(Y), len(X)))

    # delta = len(Y)
    # delta = 10 bien pour 10x10
    # delta = 8-15 bien pour 50x50
    # delta = 10-65 bien pour 100
    # en vrai apparament delta = 165 ca marche aussi pour 10x10 donc est ce que ca sert a qqch

    delta = 160  # faudra jouer plus avec

    for i in range(len(Y)):
        for j in range(len(X)):
            # générer l'altitude d'un point en fonction de celles de ceux au nord et de l'ouest
            # (s'ils sont definis)
            if j > 0 and i > 0: # cas classique
                valWest = rd.uniform(L[i][j-1] - delta, L[i][j-1] + delta)
                valNorth = rd.uniform(L[i-1][j] - delta, L[i-1][j] + delta)
                L[i][j] = (valWest + valNorth) / 2
            elif j > 0: # cas premier parallele : tout au nord
                val = rd.uniform(L[i][j-1] - delta, L[i][j-1] + delta)
                L[i][j] = val
            elif i > 0: # cas premier meridien : tout a l'ouest
                val = rd.uniform(L[i-1][j] - delta, L[i-1][j] + delta)
                L[i][j] = val
            else: # cas pole nord-ouest : premiere case
                val = rd.uniform(-len(Y), len(Y))
                L[i][j] = val
    return L

def smooth(L: np.ndarray) -> np.ndarray:
    M = np.zeros(L.shape)

    # center
    for i in range(1, L.shape[0] - 1):
        for j in range(1, L.shape[1] - 1, ):
            s = L[i - 1][j - 1]
            s += L[i - 1][j]
            s += L[i - 1][j + 1]
            s += L[i][j - 1]
            s += L[i][j]
            s += L[i][j + 1]
            s += L[i + 1][j - 1]
            s += L[i + 1][j]
            s += L[i + 1][j + 1]
            M[i][j] = s / 9

    # sides (western and eastern)
    for i in range(L.shape[0]):
        # western

        s = 0
        nb_pts = 0
        if i > 0:
            s += L[i - 1][0]
            s += L[i - 1][1]
            nb_pts += 2
        if i < L.shape[0] - 1:
            s += L[i + 1][0]
            s += L[i + 1][1]
            nb_pts += 2

        s += L[i][0]
        s += L[i][1]
        nb_pts += 2
        M[i][0] = s / nb_pts

        # eastern
        s = 0
        nb_pts = 0
        if i > 0:
            s += L[i - 1][L.shape[1]-2]
            s += L[i - 1][L.shape[1]-1]
            nb_pts += 2
        if i < L.shape[0] - 1:
            s += L[i + 1][L.shape[1]-1]
            s += L[i + 1][L.shape[1]-1]
            nb_pts += 2

        s += L[i][L.shape[1]-1]
        s += L[i][L.shape[1]-2]
        nb_pts += 2
        M[i][L.shape[1]-1] = s / nb_pts
    
    # sides (northern and southern)
    for j in range(1, L.shape[1] - 1):
        # northern
        s = 0
        s += L[0][j - 1]
        s += L[0][j]
        s += L[0][j + 1]
        s += L[1][j - 1]
        s += L[1][j]
        s += L[1][j + 1]
        M[0][j] = s / 6

        # southern
        s = 0
        s += L[L.shape[0]-2][j - 1]
        s += L[L.shape[0]-2][j]
        s += L[L.shape[0]-2][j + 1]
        s += L[L.shape[0]-1][j - 1]
        s += L[L.shape[0]-1][j]
        s += L[L.shape[0]-1][j + 1]
        M[L.shape[0]-1][j] = s / 6
    return M

def main():
    I = np.linspace(0, 100, 100)

    X, Y = np.meshgrid(I, I)
    Z = gen(X, Y)

    ax = plt.figure().add_subplot(projection='3d')
    ax.plot_surface(X, Y, Z, cmap=plt.cm.coolwarm)
    plt.show()

    ax = plt.figure().add_subplot(projection='3d')
    ax.plot_surface(X, Y, smooth(Z), cmap=plt.cm.coolwarm)
    plt.show()

if __name__ == "__main__":
    main()
