import tensorflow as tf
from tensorflow.keras.datasets import mnist

# Wczytanie danych treningowych i testowych z zestawu MNIST
(x_train, y_train), (x_test, y_test) = mnist.load_data()

# Normalizacja wartości pikseli
x_train = x_train / 255.0
x_test = x_test / 255.0

# Przekształcenie danych treningowych i testowych do postaci tensorów
x_train = tf.reshape(x_train, shape=[-1, 784])
x_test = tf.reshape(x_test, shape=[-1, 784])

# Inicjalizacja modelu lasu decyzyjnego
clf = tf.keras.RandomForestModel(n_estimators=5)

# Trenowanie modelu
clf.fit(x_train, y_train)

# Przewidywanie etykiet cyfr dla danych testowych
y_pred = clf.predict(x_test)

# Obliczenie współczynnika prawidłowej rozpoznawalności
accuracy = tf.metrics.accuracy(y_test, y_pred)
print("Test accuracy: ", accuracy.numpy())
