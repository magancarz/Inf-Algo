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
# print('Train: X=%s, y=%s' % (trainX.shape, trainy.shape))
# print('Test: X=%s, y=%s' % (testX.shape, testy.shape))

trainX = trainX.reshape((trainX.shape[0],28, 28, 1))
testX = testX.reshape((testX.shape[0], 28, 28, 1))

trainX = trainX.reshape(60000, 784)
testX = testX.reshape(10000, 784)
trainX = trainX.astype('float32')
testX = testX.astype('float32')

trainX /= 255
testX /= 255

data_slice = 60000
trainX = trainX[:data_slice,:]
trainy = trainy[:data_slice,]
testX = testX[:data_slice,:]
testy = testy[:data_slice,]

# initializing the pca
from sklearn import decomposition
pca = decomposition.PCA()

pca.n_components = 784
train_pca = pca.fit_transform(trainX)
test_pca = pca.fit_transform(testX)

from sklearn.cluster import DBSCAN

db = DBSCAN(eps=5.1, min_samples=6)
db = db.fit(train_pca)
clusters = db.fit_predict(test_pca)
core_samples_mask = np.zeros_like(db.labels_, dtype=bool)
core_samples_mask[db.core_sample_indices_] = True
labels = db.labels_
n_clusters_ = len(set(labels)) - (1 if -1 in labels else 0)
n_noise_ = list(labels).count(-1)
print('Estimated number of clusters: %d' % n_clusters_)
noise_percent = n_noise_ / len(clusters) * 100
print('Estimated number of noise percentage: %0.3f' % noise_percent)
print("Silhouette Coefficient: %0.3f" % metrics.silhouette_score(test_pca, clusters))

cluster_mapping = {}
for cluster_label, number_label in zip(clusters, testy):
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

colors = [plt.cm.Spectral(each)
          for each in np.linspace(0, 1, len(set(labels)))]

# Create a scatter plot of the clusters and noise
plt.figure(figsize=(10, 6))

# Plot the noise points
plt.scatter(test_pca[clusters == -1, 0], test_pca[clusters == -1, 1], color='gray', alpha=0.6, label='Noise')

# Plot the clusters with labels
for cluster_label, color in zip(range(n_clusters_), colors):
    cluster_points = test_pca[clusters == cluster_label]
    plt.scatter(cluster_points[:, 0], cluster_points[:, 1], color=color, alpha=0.6, label=f'Cluster {cluster_label}')
    # Label the cluster with the cluster number
    plt.annotate(str(cluster_label), (np.mean(cluster_points[:, 0]), np.mean(cluster_points[:, 1])),
                 color='black', weight='bold', fontsize=12, ha='center', va='center')

plt.title('DBSCAN Clustering Results')
plt.xlabel('Principal Component 1')
plt.ylabel('Principal Component 2')
plt.legend()
plt.show()