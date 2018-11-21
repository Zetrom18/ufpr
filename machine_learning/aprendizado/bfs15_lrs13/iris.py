import os
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from sklearn import datasets, tree
from sklearn.decomposition import PCA
from sklearn.model_selection import cross_val_score, train_test_split
from sklearn.naive_bayes import GaussianNB

# import data
iris = datasets.load_iris()

def plot2d(X, Y, I):
    # take two features.
    Xa = iris.data[:,X]
    Xb = iris.data[:,Y]
    # figure size and number
    plt.figure(I, figsize=(8, 6))
    plt.clf()
    # Plot the features
    plt.scatter(Xa[:], Xb[:], c=iris.target, cmap=plt.cm.Set1,
                edgecolor='k')
    # label axes
    plt.xlabel(iris.feature_names[X])
    plt.ylabel(iris.feature_names[Y])
    # adjust axes
    x_min, x_max = Xa[:].min() - .5, Xa[:].max() + .5
    y_min, y_max = Xb[:].min() - .5, Xb[:].max() + .5
    plt.xlim(x_min, x_max)
    plt.ylim(y_min, y_max)

    plt.xticks(())
    plt.yticks(())


def plot3d(X,Y,Z,I):
    # take three features.
    Xa = iris.data[:,X]
    Xb = iris.data[:,Y]
    Xc = iris.data[:,Z]
    # figure size and number
    fig = plt.figure(I, figsize=(8, 6))

    ax = Axes3D(fig, elev=-150, azim=110)
    
    array = []

    for i in range(len(Xa)):
        array.append([Xa[i],Xb[i],Xc[i]])
    
    # Plot the features
    X_reduced = PCA(n_components=3).fit_transform(array)
    ax.scatter(X_reduced[:, 0], X_reduced[:, 1], X_reduced[:, 2], c=iris.target,
               cmap=plt.cm.Set1, edgecolor='k', s=40)
    # label axes
    ax.set_title(iris.feature_names[X]+" X "+iris.feature_names[Y]+" X "+iris.feature_names[Z])
    ax.set_xlabel(iris.feature_names[X])
    ax.w_xaxis.set_ticklabels([])
    ax.set_ylabel(iris.feature_names[Y])
    ax.w_yaxis.set_ticklabels([])
    ax.set_zlabel(iris.feature_names[Z])
    ax.w_zaxis.set_ticklabels([])


figNo=1
# Plot each combination of 2 features in 2d
for i in range(4):
    for j in range(i+1,4):
        plot2d(i, j, figNo)
        figNo += 1

# Plot each combination of 3 features in 3d
for i in range(4):
    array = list(range(4))
    array.pop(i)
    plot3d(array[0], array[1], array[2], figNo)
    figNo += 1

# Display
plt.show()


def makeTree(file, crit):
    dTree = tree.DecisionTreeClassifier(criterion=crit, min_samples_split=6)
    dTree.fit(data_train, y_train)
    # dTree.fit(iris.data[:int(len(iris.data)/2)], iris.target[:int(len(iris.data)/2)])
    
    # export tree with graphviz
    # tree.export_graphviz(dTree,file + ".dot")
    # os.system("dot -Tpng " + file + ".dot -o " + file + ".png")

    return dTree


def makeBayes():
    gnb = GaussianNB().fit(data_train, y_train)
    return gnb


def printScore(cl, name):
    scores = cross_val_score(cl, iris.data, iris.target, cv=partitionsNo)
    print("\n" + name)
    print(scores.mean(), scores.std() * 2)


#########
infoText = "Cross val score with partition = "
partitionsNo = 5
print(infoText + str(partitionsNo))

data_train = iris.data
y_train = iris.target

giniCl = makeTree("giniTree", "gini")
printScore(giniCl, "giniTree")
entCl = makeTree("entropyTree", "entropy")
printScore(entCl, "entropyTree")
gnbCl = makeBayes()
printScore(gnbCl, "Bayes")


#########
infoText = "Split data into train and test, test="
test_size = 0.4
print("\n\n")
print(infoText + str(test_size))

giniScr = []
entScr = []
gnbScr = []
loops = 1000

for i in range(loops):
    data_train, data_test, y_train, y_test = train_test_split(iris.data, iris.target, test_size=0.4)
    giniCl = makeTree("giniTree", "gini")
    score = giniCl.score(data_test, y_test)
    # print("\nginiTree score: "+str(score))
    giniScr.append(float(score))

    entCl = makeTree("entropyTree", "entropy")
    score = entCl.score(data_test, y_test)
    # print("\nentCl score: "+str(score))
    entScr.append(score)

    gnbCl = makeBayes()
    score = gnbCl.score(data_test, y_test)
    # print("\ngnbCl score: "+str(score))
    gnbScr.append(score)


print("\n")
giniScr = np.array(giniScr)
print("Gini mean score: "+str(giniScr.mean()))
print("Variance: "+str(giniScr.std() * 2))
print("\n")

entScr = np.array(entScr)
print("Entropy mean score: "+str(entScr.mean()))
print("Variance: "+str(entScr.std() * 2))
print("\n")

gnbScr = np.array(gnbScr)
print("Bayes mean score: "+str(gnbScr.mean()))
print("Variance: "+str(gnbScr.std() * 2))






