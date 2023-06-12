import tensorflow as tf
from tensorflow import keras
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split

# Wczytanie zbioru danych MNIST
mnist = keras.datasets.mnist
(train_images, train_labels), (test_images, test_labels) = mnist.load_data()

# Przygotowanie danych
train_images = train_images.reshape((-1, 28 * 28))
test_images = test_images.reshape((-1, 28 * 28))

# Inicjalizacja i trenowanie lasu decyzyjnego
random_forest = RandomForestClassifier(n_estimators=50)
random_forest.fit(train_images, train_labels)

# Ocena wydajności lasu decyzyjnego na zbiorze testowym
predictions = random_forest.predict(test_images)
accuracy = accuracy_score(test_labels, predictions)
print("Współczynnik prawidłowej rozpoznawalności lasu decyzyjnego na zbiorze testowym:", accuracy)