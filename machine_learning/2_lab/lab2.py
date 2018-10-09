from sklearn.datasets import load_iris
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split, cross_val_score
import numpy as np

iris = load_iris()

results = {}

for k in range(3,20,2):
    knn = KNeighborsClassifier(n_neighbors=k)
    results[str(k)] = {}

    # 30 executions of 60/40 split
    scores = np.array([])
    for i in range(30):
        data_train, data_test, target_train, target_test = train_test_split(iris.data, iris.target, test_size=0.4)
        knn.fit(data_train, target_train)
        scores = np.append(scores, knn.score(data_test, target_test))
    results[str(k)]['60/40'] = "Accuracy: %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2)

    # cross_validation 5 folds
    scores = cross_val_score(knn, iris.data, iris.target, cv=5)
    results[str(k)]['cross_validation'] = "Accuracy: %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2)

for k in results.keys():
    print("+++++++++++++++++++++ K = "+k+" +++++++++++++++++++++")
    for key, val in results[k].items():
        print("    "+key+": "+val)
