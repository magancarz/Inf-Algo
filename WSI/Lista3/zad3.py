import numpy as np
import matplotlib.pyplot as plt

def L1(x, y):
    return x/(abs(x)+abs(y)), y/(abs(x)+abs(y))

def L2(x, y):
    d = np.sqrt(x**2 + y**2)
    return x/d, y/d

def relu(x):
    return np.maximum(0, x)

def relu_derivative(x):
    return np.where(x > 0, 1, 0)

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    a = sigmoid(x)
    return a * (1 - a)

def sign(x):
    if x > 0:
        return 1
    else:
        return 0

X = []
y = []

for a, b in [(1, 1), (-1, 1), (1, -1), (-1, -1)]:
    X.append([*L1(a, b)])
    y.append([sign(a) ^ sign(b)])

X = np.array(X)
y = np.array(y)

# Define the number of nodes in the hidden layer
num_hidden_nodes = 4

# Define the number of input and output nodes
num_input_nodes = X.shape[1]
num_output_nodes = y.shape[1]

# Initialize the weights for the hidden and output layers
weights_hidden = np.random.uniform(size=(num_input_nodes, num_hidden_nodes))
weights_output = np.random.uniform(size=(num_hidden_nodes, num_output_nodes))

# Define the learning rate and number of iterations
learning_rate = 0.05
num_iterations = 10

# Train the neural network
for i in range(num_iterations):
    # Forward pass
    hidden_layer_input = np.dot(X, weights_hidden)
    hidden_layer_output = relu(hidden_layer_input)
    output_layer_input = np.dot(hidden_layer_output, weights_output)
    output = relu(output_layer_input)

    # Backward pass
    error = y - output
    d_output = error * relu_derivative(output)
    error_hidden = d_output.dot(weights_output.T)
    d_hidden = error_hidden * relu_derivative(hidden_layer_output)

    # Update weights
    weights_output += hidden_layer_output.T.dot(d_output) * learning_rate
    weights_hidden += X.T.dot(d_hidden) * learning_rate

def predict(x):
    hidden_layer_input = np.dot(x, weights_hidden)
    hidden_layer_output = relu(hidden_layer_input)
    output_layer_input = np.dot(hidden_layer_output, weights_output)
    output = relu(output_layer_input)
    return output

print("Predictions on test data:")
for a, b in [(-0.6, -0.4), (-0.8, 0.2), (0.1, -0.7), (1, 0.45)]:
    prediction = predict(np.array([[*L1(a, b)]]))
    rounded_prediction = np.round(prediction)
    print(f"({a}, {b}) -> {rounded_prediction}")