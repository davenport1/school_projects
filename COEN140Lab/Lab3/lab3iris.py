# Class: COEN 140 Lab Machine Learning/Data Mining
# Name: Matthew Davenport
# Date: 9/25/2022
# Title: Lab 3 – Iris classifier
# Description: This program will perform clssifications
#           on iris datasets based on the sepal
#           lengths/widths and petal lengths/widths and 
#           classify them as Setosa, Versicolour, or Virginica



ROWS = 150
COLUMNS = 5
CLASSIFICATIONS = 3



import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib import colors
from itertools import islice

cmap = colors.LinearSegmentedColormap(
    "red_blue_classes",
    {
        "red": [(0, 1, 1), (1, 0.7, 0.7)],
        "green": [(0, 0.7, 0.7), (1, 0.7, 0.7)],
        "blue": [(0, 0.7, 0.7), (1, 1, 1)],
    },
)
plt.cm.register_cmap(cmap=cmap)

ROWS = 150
COLUMNS = 5
CLASSIFICATIONS = 3

# for testing of proper reading of data (provided)
def test_dataset(data):
    if len(data) != 150:
        return False
    for row in data:
        if len(row) != 5:
            return False
        for column in row[:-1]:
            if type(column) != np.float64:
                return False
            
        if type(row[-1]) != str:
            return False
    
    return True

#read the file and convert the contents to the proper types and return list of lists
def read_file(): 
    data = [[] for x in range(ROWS)]                 # initialize empty list of lists length 150
    file = open('test_dataset.txt', 'r')            # open file as read
    contents = [line.split() for line in file]      # put contents of file into list of lists of characters
    
    #iterate through contents stopping at each , in the list of characters to convert the first 4 elements into 
    #           np.float64 nd the last into a string to be loaded into data
    for row in range(len(contents)):                # iterate through contents
        i = 0
        for s in contents[row][0].split(","):       # usingn , as delimiter
            if i == (COLUMNS - 1):                              # at the last element just append as string
                data[row].append(s)
                break
            i += 1
            data[row].append(np.float64(s))         # append into data[row] the number converted to np.float64
    return data

#passed data and calculates covariance matrix
def cov_matrix(data):
    A = []
    B = []
    C = []
    D = []
    for row in data:
        A.append(row[0])
        B.append(row[1])
        C.append(row[2])
        D.append(row[3])
    new_data = np.array([A,B,C,D])
    covMatrix = np.cov(new_data, bias=True)
    return covMatrix






from scipy import linalg 

###### plot_data taken from scipy ########
def plot_data(lda, X, y, y_pred, fig_index):
    splot = plt.subplot(2, 2, fig_index)
    if fig_index == 1:
        plt.title("Linear Discriminant Analysis")
        plt.ylabel("Data with\n fixed covariance")
    elif fig_index == 2:
        plt.title("Quadratic Discriminant Analysis")
    elif fig_index == 3:
        plt.ylabel("Data with\n varying covariances")

    tp = y == y_pred  # True Positive
    tp0, tp1 = tp[y == 0], tp[y == 1]
    X0, X1 = X[y == 0], X[y == 1]
    X0_tp, X0_fp = X0[tp0], X0[~tp0]
    X1_tp, X1_fp = X1[tp1], X1[~tp1]

    # class 0: dots
    plt.scatter(X0_tp[:, 0], X0_tp[:, 1], marker=".", color="red")
    plt.scatter(X0_fp[:, 0], X0_fp[:, 1], marker="x", s=20, color="#990000")  # dark red

    # class 1: dots
    plt.scatter(X1_tp[:, 0], X1_tp[:, 1], marker=".", color="blue")
    plt.scatter(
        X1_fp[:, 0], X1_fp[:, 1], marker="x", s=20, color="#000099"
    )  # dark blue

    # class 0 and 1 : areas
    nx, ny = 200, 100
    x_min, x_max = plt.xlim()
    y_min, y_max = plt.ylim()
    xx, yy = np.meshgrid(np.linspace(x_min, x_max, nx), np.linspace(y_min, y_max, ny))
    Z = lda.predict_proba(np.c_[xx.ravel(), yy.ravel()])
    Z = Z[:, 1].reshape(xx.shape)
    plt.pcolormesh(
        xx, yy, Z, cmap="red_blue_classes", norm=colors.Normalize(0.0, 1.0), zorder=0
    )
    plt.contour(xx, yy, Z, [0.5], linewidths=2.0, colors="white")

    # means
    plt.plot(
        lda.means_[0][0],
        lda.means_[0][1],
        "*",
        color="yellow",
        markersize=15,
        markeredgecolor="grey",
    )
    plt.plot(
        lda.means_[1][0],
        lda.means_[1][1],
        "*",
        color="yellow",
        markersize=15,
        markeredgecolor="grey",
    )

    return splot

############ plot_ellipse taken from scipy ###################
def plot_ellipse(splot, mean, cov, color):
    v, w = linalg.eigh(cov)
    u = w[0] / linalg.norm(w[0])
    angle = np.arctan(u[1] / u[0])
    angle = 180 * angle / np.pi  # convert to degrees
    # filled Gaussian at 2 standard deviation
    ell = mpl.patches.Ellipse(
        mean,
        2 * v[0] ** 0.5,
        2 * v[1] ** 0.5,
        180 + angle,
        facecolor=color,
        edgecolor="black",
        linewidth=2,
    )
    ell.set_clip_box(splot.bbox)
    ell.set_alpha(0.2)
    splot.add_artist(ell)
    splot.set_xticks(())
    splot.set_yticks(())

################### plot_lda_cov && plot_qda_cov taken from scipy #########################
def plot_lda_cov(lda, splot):
    plot_ellipse(splot, lda.means_[0], lda.covariance_, "red")
    plot_ellipse(splot, lda.means_[1], lda.covariance_, "blue")


def plot_qda_cov(qda, splot):
    plot_ellipse(splot, qda.means_[0], qda.covariance_[0], "red")
    plot_ellipse(splot, qda.means_[1], qda.covariance_[1], "blue")      








###################################################### TESTING ############################################################
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis as LDA
from sklearn.discriminant_analysis import QuadraticDiscriminantAnalysis as QDA

# Testing contentes of file converted successfully 
data = read_file()
print(test_dataset(data))

# split into training and testing lists 
training = data[:40:] + data[50:90:] + data[100:140:]
testing = data[40:50:] + data[90:100:] + data[140:150:]

lda_matrix = cov_matrix(training)
print(lda_matrix)

print(len(training))
print(len(testing))

# need to apply this to our code. 
for i, (X, y) in enumerate([dataset_fixed_cov(), dataset_cov()]):
    # Linear Discriminant Analysis
    lda = LDA(solver="svd", store_covariance=True)
    y_pred = lda.fit(X, y).predict(X)
    splot = plot_data(lda, X, y, y_pred, fig_index=2 * i + 1)
    plot_lda_cov(lda, splot)
    plt.axis("tight")

    # Quadratic Discriminant Analysis
    qda = QDA(store_covariance=True)
    y_pred = qda.fit(X, y).predict(X)
    splot = plot_data(qda, X, y, y_pred, fig_index=2 * i + 2)
    plot_qda_cov(qda, splot)
    plt.axis("tight")
