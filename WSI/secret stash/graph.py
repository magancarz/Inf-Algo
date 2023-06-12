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

# print("Train matrix shape", trainX.shape)
# print("Test matrix shape", testX.shape)

# data_slice = 10000
# trainX = trainX[:data_slice,:]
# trainy = trainy[:data_slice,]
# testX = testX[:data_slice,:]
# testy = testy[:data_slice,]

print(trainX.shape)
print(trainy.shape)

# initializing the pca
from sklearn import decomposition
pca = decomposition.PCA()

# configuring the parameteres
# the number of components = 2
pca.n_components = 2
pca_data = pca.fit_transform(trainX)

# pca_reduced will contain the 2-d projects of simple data
print("shape of pca_reduced.shape = ", pca_data.shape)

# attaching the label for each 2-d data point 
pca_data = np.vstack((pca_data.T, trainy)).T

# creating a new data fram which help us in ploting the result data
pca_df = pd.DataFrame(data=pca_data, columns=("1st_principal", "2nd_principal", "label"))
sn.FacetGrid(pca_df, hue="label", height=6).map(plt.scatter, '1st_principal', '2nd_principal').add_legend()
plt.show()