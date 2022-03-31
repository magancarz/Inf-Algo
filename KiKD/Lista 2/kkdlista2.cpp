#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <iomanip>

unsigned int initialFileSize = 0;
unsigned int finalFileSize = 0;
double compressionRatio = 0;
double entropy = 0;

double calculate_entropy(std::ifstream* file) {
	int characters[256] = {0};
	int size = 0;
	unsigned char letter = 0;
	
	while (!file -> eof()) {
	    characters[letter]++;

	    letter = file -> get();

	    size++;
	}

	//calculate entropy
	double log2lsize = std::log2l(size);
	double sum = 0;

	for(int i = 0; i < 256; i++) {
		if(characters[i] != 0) {
			sum += characters[i] * std::log2l(characters[i]);
		}
	}
	double sum_divided_by_size = sum / (double) size;
	return log2lsize - sum_divided_by_size;
}

// A Tree node
struct Node {
	char ch;
	int freq;
	Node *left, *right;
};

// Function to allocate a new tree node
Node* getNode(char ch, int freq, Node* left, Node* right) {
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

// Comparison object to be used to order the heap
struct comp {
	bool operator()(Node* l, Node* r) {
		// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};

// traverse the Huffman Tree and store Huffman Codes
// in a map.
void encode(Node* root, std::string str,
			std::unordered_map<char, std::string> &huffmanCode) {
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

// traverse the Huffman Tree and decode the encoded string
void decode(Node* root, int &index, std::string str) {
	if (root == nullptr) {
		return;
	}

	// found a leaf node
	if (!root->left && !root->right) {
		std::cout << root->ch;
		return;
	}

	index++;

	if (str[index] =='0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

// Builds Huffman Tree and decode given input text
void buildHuffmanTree(std::string text) {
	// count frequency of appearance of each character
	// and store it in a map
	std::unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	// Create a priority queue to store live nodes of
	// Huffman tree;
	std::priority_queue<Node*, std::vector<Node*>, comp> pq;

	// Create a leaf node for each character and add it
	// to the priority queue.
	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// do till there is more than one node in the queue
	while (pq.size() != 1) {
		// Remove the two nodes of highest priority
		// (lowest frequency) from the queue
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		// Create a new internal node with these two nodes
		// as children and with frequency equal to the sum
		// of the two nodes' frequencies. Add the new node
		// to the priority queue.
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// root stores pointer to root of Huffman Tree
	Node* root = pq.top();

	// traverse the Huffman Tree and store Huffman Codes
	// in a map. Also prints them
	std::unordered_map<char, std::string> huffmanCode;
	encode(root, "", huffmanCode);

	std::cout << "Huffman Codes are :\n" << '\n';
	for (auto pair: huffmanCode) {
		std::cout << pair.first << " " << pair.second << '\n';
	}

	std::cout << "\nOriginal string was :\n" << text << '\n';

	// print encoded string
	std::string str = "";
	for (char ch: text) {
		str += huffmanCode[ch];
	}

	std::cout << "\nEncoded string is :\n" << str << '\n';
	finalFileSize = str.size();
	compressionRatio = finalFileSize / initialFileSize;
	
	std::cout << "Entropy: " << entropy << std::endl;

	// traverse the Huffman Tree again and this time
	// decode the encoded string
	int index = -1;
	std::cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
	std::cout << std::endl;
	std::ofstream file ("decoded.txt");
	if(file.is_open()) {
		file << str;
		file.close();
	} else { std::cout << "Unable to open file."; }
	std::cout << "Saved to the file.\n";
}

// Huffman coding algorithm
int main(int argc, char* argv[]) {
/*
	if(argc < 2) {
		std::cout << "Add filename argument\n";
		return 1;
	}
	std::ifstream file(argv[1], std::ios::in | std::ios::binary);
	if(!file.is_open()) {
		std::cerr << "Could not open the file '" << argv[1] << "'" << std::endl;
		return 1;
	}
	*/

	//double entropy = calculate_entropy(&file);

	std::ifstream file("PanTadeusz");
	//std::ifstream file(argv[1], std::ios::in | std::ios::binary);
	//entropy = calculate_entropy(&t);
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string text = buffer.str();
	initialFileSize = text.size();
	
	auto start = std::chrono::high_resolution_clock::now();
	buildHuffmanTree(text);
	auto end = std::chrono::high_resolution_clock::now();
	
	
	std::cout << "Compression ratio: " << compressionRatio << "%\n";
	std::cout << std::setprecision(15) << "Huffman coding time: " <<  std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000000000.0 << std::endl;

	return 0;
}
