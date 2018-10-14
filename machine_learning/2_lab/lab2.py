from sklearn.datasets import load_iris
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split, cross_val_score
import matplotlib.pyplot as plt
import numpy as np

iris = load_iris()

results = {
}

for k in range(3,50,2):
    knn = KNeighborsClassifier(n_neighbors=k)
    results[str(k)] = {}

    # 30 executions of 60/40 split
    scores = np.array([])
    for i in range(30):
        data_train, data_test, target_train, target_test = train_test_split(iris.data, iris.target, test_size=0.4)
        knn.fit(data_train, target_train)
        scores = np.append(scores, knn.score(data_test, target_test))
    results[str(k)]['60/40'] = scores

    # cross_validation 5 folds
    scores = cross_val_score(knn, iris.data, iris.target, cv=5)
    results[str(k)]['cross_validation'] = scores

x = []
y_split = []
y_cross = []

for k in results.keys():
    print("+++++++++++++++++++++ K = "+k+" +++++++++++++++++++++")
    x.append(k)
    for key, val in results[k].items():
        if key == "60/40":
            y_split.append(val.mean())
        elif key == "cross_validation":
            y_cross.append(val.mean())
        print("    "+key+": "+"Accuracy: %0.2f (+/- %0.2f)" % (val.mean(), val.std() * 2))

plt.plot(x, y_split)
plt.show()

plt.plot(x, y_cross)
plt.show()
