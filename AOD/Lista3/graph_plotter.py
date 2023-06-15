import csv
import os

path = 'data\\'

for filename in os.listdir(path):
    data = []
    with open(path + filename, 'r') as file:
        reader = csv.reader(file, delimiter='&')
        for row in reader:
            row_values = []
            for val in row:
                val = val.strip()
                if val.isdigit():
                    row_values.append(int(val))
                else:
                    try:
                        row_values.append(float(val))
                    except ValueError:
                        continue
            data.append(row_values)

    # Extract the desired columns
    fourth_col = [row[3] for row in data]
    sixth_col = [row[5] for row in data]
    eighth_col = [row[7] for row in data]

    # Plot the graph using matplotlib
    import matplotlib.pyplot as plt

    plt.plot(fourth_col, label='Dijkstra')
    plt.plot(sixth_col, label='Dial')
    plt.plot(eighth_col, label='Radix')

    plt.xlabel('Graph')
    plt.ylabel('Time (ms)')
    plt.title(f'Time Comparision for {filename}')
    plt.legend()
    plt.savefig(f'graph_{filename}.png')
    plt.show()