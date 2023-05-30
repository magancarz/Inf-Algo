CC = g++
CFLAGS = -std=c++20 -Ofast

SRC = Graph.cpp DijkstraBenchmark.cpp dijkstraImpl/Dijsktra.cpp Graph.h DijkstraBenchmark.h dijkstraImpl/Dijkstra.h
DIJKSTRA = dijkstra
DIAL = dial
RADIX = radixheap

all: $(DIJKSTRA) $(DIAL) $(RADIX)

$(DIJKSTRA): dijkstra.cpp $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

$(DIAL): dial.cpp $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

$(RADIX): radixheap.cpp $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(DIJKSTRA) $(DIAL) $(RADIX)