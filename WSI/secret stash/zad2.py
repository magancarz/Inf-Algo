import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import tensorflow as tf
import matplotlib.patheffects as PathEffect
from matplotlib import offsetbox
import plotly.graph_objects as go
from time import time
import sys
from tensorflow.keras.utils import to_categorical
from keras.utils import to_categorical
import sklearn.metrics as metrics
from sklearn.metrics import silhouette_score
from keras.datasets import mnist 
import seaborn as sn

(trainX, trainy), (testX, testy) = mnist.load_data()

trainX = trainX.reshape((trainX.shape[0],28, 28, 1))
testX = testX.reshape((testX.shape[0], 28, 28, 1))

trainX = trainX.reshape(60000, 784)
testX = testX.reshape(10000, 784)
trainX = trainX.astype('float32')
testX = testX.astype('float32')

trainX /= 255
testX /= 255

data_slice = 1000
trainX = trainX[:data_slice,:]
trainy = trainy[:data_slice,]
testX = testX[:data_slice,:]
testy = testy[:data_slice,]

# initializing the pca
from sklearn import decomposition
pca = decomposition.PCA()

pca.n_components = 15
train_pca = pca.fit_transform(trainX)
test_pca = pca.fit_transform(testX)

import numpy

def DBSCAN(D, eps, MinPts):  
    labels = [0]*len(D) 
    C = 0
    
    for P in range(0, len(D)):
        if not (labels[P] == 0):
           continue
        
        NeighborPts = regionQuery(D, P, eps)
        
        if len(NeighborPts) < MinPts:
            labels[P] = -1  
        else: 
           C += 1
           growCluster(D, labels, P, NeighborPts, C, eps, MinPts)
    
    return labels


def growCluster(D, labels, P, NeighborPts, C, eps, MinPts):
    labels[P] = C

    i = 0
    while i < len(NeighborPts):
        Pn = NeighborPts[i]

        if labels[Pn] == -1:
            labels[Pn] = C

        elif labels[Pn] == 0:
            labels[Pn] = C

            PnNeighborPts = regionQuery(D, Pn, eps)
            if len(PnNeighborPts) >= MinPts:
                NeighborPts.extend(PnNeighborPts)

        i += 1

def regionQuery(D, P, eps):
    neighbors = []
    
    for Pn in range(0, len(D)):
        
        if numpy.linalg.norm(D[P] - D[Pn]) < eps:
           neighbors.append(Pn)
            
    return neighbors

db = DBSCAN(train_pca, 3, 5)
unique_numbers, counts = np.unique(db, return_counts=True)
noise_percent = counts[0] / len(trainX) * 100
print(f"Noise percent: {noise_percent:.2f}%")

cluster_mapping = {}
for cluster_label, number_label in zip(db, trainy):
    if cluster_label in cluster_mapping:
        cluster_mapping[cluster_label].append(number_label)
    else:
        cluster_mapping[cluster_label] = [number_label]

for cluster_label, numbers in cluster_mapping.items():
	 if cluster_label != -1:
	    unique_numbers, counts = np.unique(numbers, return_counts=True)
	    most_common_index = np.argmax(counts)
	    most_common_number = unique_numbers[most_common_index]
	    count = counts[most_common_index]
	    percentage = 100.0 - ((count / len(numbers)) * 100)
	    print(f"Cluster {cluster_label} with most common number {most_common_number} has missclassification percentage = {percentage:.2f}%")

from sklearn import metrics

accuracy = metrics.accuracy_score(testy, labels)

print("Accuracy:", accuracy)

from scipy.stats import mode

cluster_mapping = {}
for cluster_label, number_label in zip(clusters, testy):
    if cluster_label in cluster_mapping:
        cluster_mapping[cluster_label].append(number_label)
    else:
        cluster_mapping[cluster_label] = [number_label]

total_samples = len(testy)

# Find the most common number and its percentage in each cluster
for cluster_label, numbers in cluster_mapping.items():
    unique_numbers, counts = np.unique(numbers, return_counts=True)
    most_common_index = np.argmax(counts)
    most_common_number = unique_numbers[most_common_index]
    count = counts[most_common_index]
    percentage = (count / len(numbers)) * 100
    print(f"Cluster {cluster_label}: Most common number = {most_common_number}, Percentage = {percentage:.2f}%")