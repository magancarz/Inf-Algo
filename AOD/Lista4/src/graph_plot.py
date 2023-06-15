import pandas as pd
import matplotlib.pyplot as plt

# #Load CSV file into a DataFrame
# df = pd.read_csv('data1.csv', header=None)
# x = df[0]
# y = df[1]

# # Create a graph using matplotlib
# plt.plot(x, y)
# plt.xlabel('k')
# plt.ylabel('Augmenting Paths')
# plt.title('Average Number Of Augmenting Paths')
# plt.savefig("ex11.png")
# plt.show()

# df = pd.read_csv('data2.csv', header=None)
# x = df[0]
# y = df[1]

# # Create a graph using matplotlib
# plt.plot(x, y)
# plt.xlabel('k')
# plt.ylabel('Max Flow')
# plt.title('Average Number Of Max Flow')
# plt.savefig("ex12.png")
# plt.show()

# df = pd.read_csv('data3.csv', header=None)
# x = df[0]
# y = df[1]

# # Create a graph using matplotlib
# plt.plot(x, y)
# plt.xlabel('k')
# plt.ylabel('Time (microseconds)')
# plt.title('Average Time')
# plt.savefig("ex13.png")
# plt.show()

for k in range(3, 11, 1):
	df = pd.read_csv(f'k{k}.csv', header=None)
	x = df[0]
	y = df[1]

	# Create a graph using matplotlib
	plt.plot(x, y)
	plt.xlabel('i')
	plt.ylabel('Average Size Of Maximum Matching Set Count')
	plt.title(f'Average Size Of Maximum Matching Set Count Per i For k={k}')
	plt.savefig(f'ex2k{k}.png')
	plt.show()

for i in range(1, 11, 1):
	df = pd.read_csv(f'i{i}.csv', header=None)
	x = df[0]
	y = df[1]

	# Create a graph using matplotlib
	plt.plot(x, y)
	plt.xlabel('k')
	plt.ylabel('Average Time (microseconds)')
	plt.title(f'Average Time Per k For i={i}')
	plt.savefig(f'ex2i{i}.png')
	plt.show()