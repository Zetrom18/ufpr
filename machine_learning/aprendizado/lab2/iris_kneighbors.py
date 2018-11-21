from sklearn.neighbors import KNeighborsClassifier
from sklearn.datasets import load_iris
from sklearn.metrics import confusion_matrix
from sklearn.model_selection import train_test_split, cross_val_predict, cross_val_score
from scipy.stats import wilcoxon
import matplotlib.pyplot as plt
import numpy as np

iris = load_iris()

cv_scores = []
ts_scores = []

for k in range(1, 20):
    neigh = KNeighborsClassifier(n_neighbors=k)

    cv_scores.append(cross_val_score(neigh, iris.data, iris.target, cv=5).mean())

    ts_score_i = []

    for i in range(30):
        data_train, data_test, target_train, target_test = train_test_split(iris.data, iris.target, test_size=0.4)
        neigh.fit(data_train, target_train)
        ts_score_i.append(neigh.score(data_test, target_test))
    ts_scores.append(sum(ts_score_i)/len(ts_score_i))

    print("K: "+str(k)+" CrossValScore: "+str(cv_scores[k-1])+" TrainTestSplitScore: "+str(ts_scores[k-1]))

# plt.plot(range(1,20), cv_scores)

#    ts_scores = []
#    for i in range(30):
#        data_train, data_test, target_train, target_test = train_test_split(iris.data, iris.target, test_size=0.4)
#        neigh.fit(data_train, target_train)
#        ts_scores.append(neigh.score(data_test, target_test))
#
#    cv_mean_score = cv_scores.mean()
#    ts_mean_score = sum(ts_scores)/len(ts_scores)
#    mean_score = (ts_mean_score+ts_mean_score)/2
#
#    classifiers_scores.append({
#        "k": k,
#        "mean_score": mean_score;
#        "scores": np.concatenate([np.array(cv_scores),np.array(ts_scores)]),
#        })
#
#    print("\nResultados para "+str(k)+" vizinhos")
#    print("Validacao cruzada: "+str(cv_mean_score))
#    print("Media de 30 execucoes de treino/teste (60/40): "+str(ts_mean_score))
#    print("Media final: "+str(mean_score))
#
#for i in range(len(classifiers_scores)):
#    for j in range(len(classifiers_scores)):
#        if i==j:
#            continue
#        print(wilcoxon(classifiers_scores[i]['scores'],classifiers_scores[j]['scores']))
