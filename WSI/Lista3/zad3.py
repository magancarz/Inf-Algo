import numpy as np

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    return x * (1 - x)

def relu(x):
    return np.maximum(0, x)

def relu_derivative(x):
    return np.where(x <= 0, 0, 1)

def normalize_l1(x):
    return x / np.sum(np.abs(x))

def normalize_l2(x):
    norm = np.linalg.norm(x)
    return x / norm if norm != 0 else x

class TwoLayerNN:
    def __init__(self, learning_rate=0.1):
        self.learning_rate = learning_rate
        self.weights_hidden = np.random.uniform(-1, 1, (2, 4))
        self.bias_hidden = np.random.uniform(-1, 1, (1, 4))
        self.weights_output = np.random.uniform(-1, 1, (4, 1))
        self.bias_output = np.random.uniform(-1, 1, (1, 1))

    def forward_pass(self, x):
        self.hidden_layer = sigmoid(np.dot(x, self.weights_hidden) + self.bias_hidden)
        self.output = sigmoid(np.dot(self.hidden_layer, self.weights_output) + self.bias_output)
        return self.output

    def backward_pass(self, x, y):
        error_output = y - self.output
        delta_output = error_output * sigmoid_derivative(self.output)
        error_hidden = np.dot(delta_output, self.weights_output.T)
        delta_hidden = error_hidden * sigmoid_derivative(self.hidden_layer)

        self.weights_output += self.learning_rate * np.dot(self.hidden_layer.T, delta_output)
        self.bias_output += self.learning_rate * np.sum(delta_output, axis=0, keepdims=True)
        self.weights_hidden += self.learning_rate * np.dot(x.T, delta_hidden)
        self.bias_hidden += self.learning_rate * np.sum(delta_hidden, axis=0, keepdims=True)

    def train(self, x, y, num_epochs=1000):
        for _ in range(num_epochs):
            self.forward_pass(x)
            self.backward_pass(x, y)

    def predict(self, x):
        return np.round(self.forward_pass(x))

# Testing the implementation

# Non-normalized data
X = np.array([[0.8, -0.6], [-0.4, 0.2], [0.3, 0.9]])
Y = np.array([[1], [0], [1]])

model = TwoLayerNN()
model.train(X, Y)

print("Non-normalized data:")
for x, y in zip(X, Y):
    prediction = model.predict(x)
    print("Input:", x, "Expected:", y, "Predicted:", prediction.ravel())

# L1-normalized data
X_norm_l1 = normalize_l1(X)

model = TwoLayerNN()
model.train(X_norm_l1, Y)

print("\nL1-normalized data:")
for x, y in zip(X_norm_l1, Y):
    prediction = model.predict(x)
    print("Input:", x, "Expected:", y, "Predicted:", prediction.ravel())

# L2-normalized data
X_norm_l2 = normalize_l2(X)

model = TwoLayerNN()
model.train(X_norm_l2, Y)

print("\nL2-normalized data:")
for x, y in zip(X_norm_l2, Y):
    prediction = model.predict(x)
    print("Input:", x, "Expected:", y, "Predicted:", prediction.ravel())

# ReLU activation
class TwoLayerNN_ReLU(TwoLayerNN):
    def forward_pass(self, x):
        self.hidden_layer = relu(np.dot(x, self.weights_hidden) + self.bias_hidden)
        self.output = sigmoid(np.dot(self.hidden_layer, self.weights_output) + self.bias_output)
        return self.output

model_relu = TwoLayerNN_ReLU()
model_relu.train(X, Y)

print("\nReLU activation:")
for x, y in zip(X, Y):
    prediction = model_relu.predict(x)
    print("Input:", x, "Expected:", y, "Predicted:", prediction.ravel())
