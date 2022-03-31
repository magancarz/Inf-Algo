#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <iomanip>

// variables
unsigned int initialFileSize = 0;
unsigned int finalFileSize = 0;
double entropy = 0;

double calculate_entropy(std::ifstream* file) {
	int characters[256] = {0};
	int size = 0;
	unsigned char letter = 0;
	
	while (!file -> eof()) {
	    characters[letter]++;

	    // get the next character
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

struct Node {
	char ch;
	int freq;
	Node *left, *right;
};

Node* getNode(char ch, int freq, Node* left, Node* right) {
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

struct comp {
	bool operator()(Node* l, Node* r) {
		return l->freq > r->freq;
	}
};

void encode(Node* root, std::string str,
			std::unordered_map<char, std::string> &huffmanCode) {
	if (root == nullptr)
		return;

	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int &index, std::string str) {
	if (root == nullptr) {
		return;
	}

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

void buildHuffmanTree(std::string text) {
	std::unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	std::priority_queue<Node*, std::vector<Node*>, comp> pq;

	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1) {
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	Node* root = pq.top();

	std::unordered_map<char, std::string> huffmanCode;
	encode(root, "", huffmanCode);

	std::cout << "Huffman Codes are :\n" << '\n';
	for (auto pair: huffmanCode) {
		std::cout << pair.first << " " << pair.second << '\n';
	}

	std::cout << "\nOriginal string was :\n" << text << '\n';

	std::string str = "";
	for (char ch: text) {
		str += huffmanCode[ch];
	}

	std::cout << "\nEncoded string is :\n" << str << '\n';
	finalFileSize = str.size();
	std::cout << "Compression ratio: " << finalFileSize / initialFileSize << "%\n";
	
	std::cout << "Entropy: " << entropy << std::endl;

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

	std::ifstream file("Kordian");
	//std::ifstream file(argv[1], std::ios::in | std::ios::binary);
	//entropy = calculate_entropy(&t);
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string text = buffer.str();
	initialFileSize = text.size();
	
	auto start = std::chrono::high_resolution_clock::now();
	buildHuffmanTree(text);
	auto end = std::chrono::high_resolution_clock::now();
	
	std::cout << std::setprecision(15) << "Huffman coding time: " <<  std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000000000.0 << std::endl;

	return 0;
}
