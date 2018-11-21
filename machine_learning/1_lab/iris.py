import os
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from sklearn import datasets, tree
from sklearn.decomposition import PCA
from sklearn.model_selection import cross_val_score, train_test_split
from sklearn.naive_bayes import GaussianNB

def plot2d(X, Y, I):
    # we only take two features.
    Xa = iris.data[:,X]
    Xb = iris.data[:,Y]

    x_min, x_max = Xa[:].min() - .5, Xa[:].max() + .5
    y_min, y_max = Xb[:].min() - .5, Xb[:].max() + .5

    plt.figure(I, figsize=(8, 6))
    plt.clf()

    # Plot the training points
    plt.scatter(Xa[:], Xb[:], c=y, cmap=plt.cm.Set1,
                edgecolor='k')

    plt.xlabel(iris.feature_names[X])
    plt.ylabel(iris.feature_names[Y])

    plt.xlim(x_min, x_max)
    plt.ylim(y_min, y_max)
    plt.xticks(())
    plt.yticks(())
    

def plot3d(X,Y,Z,I):
    # To getter a better understanding of interaction of the dimensions
    # plot the first three PCA dimensions

    # we only take three features.
    Xa = iris.data[:,X]
    Xb = iris.data[:,Y]
    Xc = iris.data[:,Z]

    fig = plt.figure(I, figsize=(8, 6))
    ax = Axes3D(fig, elev=-150, azim=110)

    array = []

    for i in range(len(Xa)):
        array.append([Xa[i],Xb[i],Xc[i]])

    X_reduced = PCA(n_components=3).fit_transform(array)
    ax.scatter(X_reduced[:, 0], X_reduced[:, 1], X_reduced[:, 2], c=y,
               cmap=plt.cm.Set1, edgecolor='k', s=40)
    ax.set_title("First three PCA directions")
    ax.set_xlabel(iris.feature_names[X])
    ax.w_xaxis.set_ticklabels([])
    ax.set_ylabel(iris.feature_names[Y])
    ax.w_yaxis.set_ticklabels([])
    ax.set_zlabel(iris.feature_names[Z])
    ax.w_zaxis.set_ticklabels([])


# import some data to play with
iris = datasets.load_iris()

y = iris.target

count=1

for i in range(4):
    for j in range(i+1,4):
        plot2d(i,j,count)
        count += 1


for i in range(4):
    array = range(4)
    array.pop(i)
    plot3d(array[0],array[1],array[2],count)
    count += 1

# plt.show()


def makeTree(file, crit):
    giniTree = tree.DecisionTreeClassifier(criterion=crit, min_samples_split=2)
    giniTree.fit(data_train, y_train)
    # giniTree.fit(iris.data[:int(len(iris.data)/2)], iris.target[:int(len(iris.data)/2)])
    scores = cross_val_score(giniTree, iris.data, iris.target, cv=25)
    print(scores.mean(), scores.std() * 2)

    score = giniTree.score(data_test, y_test)
    print("\nTree " + crit + " score: "+str(score))

    tree.export_graphviz(giniTree,file + ".dot")
    os.system("dot -Tpng " + file + ".dot -o " + file + ".png")

    return score




def makeBayes():
    gnb = GaussianNB().fit(data_train, y_train)
    # y_pred = gnb.predict(iris.data)
    score = gnb.score(data_test, y_test)
    scores = cross_val_score(gnb, iris.data, iris.target, cv=25)
    print(scores.mean(), scores.std() * 2)
    print("\nBayes score: "+str(score))
    # print("Number of mislabeled points out of a total %d points : %d"
          # % (iris.data.shape[0],(iris.target != y_pred).sum()))
    return score

giniScr = 0
entScr = 0
gnbScr = 0
loops = 1

for i in range(loops):
    data_train, data_test, y_train, y_test = train_test_split(iris.data, iris.target, test_size=0.9)
    giniScr += makeTree("giniTree", "gini")
    entScr += makeTree("entropyTree", "entropy")
    gnbScr += makeBayes()

print("\n\n\n")
print("Gini mean score: "+str(giniScr/loops))
print("Entropy mean score: "+str(entScr/loops))
print("Bayes mean score: "+str(gnbScr/loops))






