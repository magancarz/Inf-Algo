import numpy as np
import tensorflow as tf
from sklearn.cluster import DBSCAN
from sklearn.metrics import accuracy_score

mnist = tf.keras.datasets.mnist
(x_train, y_train), _ = mnist.load_data()

# Preprocessing danych: spłaszczenie obrazów i normalizacja wartości pikseli
x_train = x_train.reshape(-1, 784)
x_train = x_train / 255.0


# Inicjalizacja i uruchomienie algorytmu DBSCAN
#jak dobrać odpowiednią wartośc ?
eps = 3  # Wartość sąsiedztwa
min_samples = 10  # Minimalna liczba punktów w sąsiedztwie

dbscan = DBSCAN(eps=eps, min_samples=min_samples)
clusters = dbscan.fit_predict(x_train)

print(clusters)

# Obliczenie procentowego udziału szumu
noise_percentage = np.mean(clusters == -1) * 100

#Obliczenie liczby unikalnych klastrów
#chcemy aby klaststrów było od 10 do 30
unique_clusters = np.unique(clusters)
num_clusters = len(unique_clusters) - 1  # Pomijamy etykietę dla szumu (-1)

print("unique clusters num", num_clusters)
print("unique clusters", unique_clusters)

# Utworzenie mapowania klastrów do etykiet cyfr
cluster_labels = {}
for cluster_id in unique_clusters:
    if cluster_id != -1:
        cluster_points = y_train[clusters == cluster_id]
        if len(cluster_points) > 0:
            cluster_label = np.argmax(np.bincount(cluster_points))
            cluster_labels[cluster_id] = cluster_label

# Klasifikacja klastrów i obliczenie dokładności
y_pred = np.array([cluster_labels[cluster] if cluster != -1 and cluster in cluster_labels else -1 for cluster in clusters])
accuracy = accuracy_score(y_train, y_pred) * 100

# Obliczenie procentowego udziału błędnych klasyfikacji w wyznaczonych klastrach
misclassification_percentage = (np.sum(y_train != y_pred) / len(y_train[y_pred != -1])) * 100


print("Liczba klastrow: ", num_clusters)
print("Dokladnosc klasyfikacji: {:.2f}%".format(accuracy))
print("Procent szumu: {:.2f}%".format(noise_percentage))
print("Procent blędnych klasyfikacji w wyznaczonych klastrach: {:.2f}%".format(misclassification_percentage))