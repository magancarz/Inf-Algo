#include <fstream>
#include <iostream>
#include <cmath>

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

double calculate_conditional_entropy(std::ifstream* file) {
	int double_characters[256][256];
	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			double_characters[i][j] = 0;
		}
	}

	int characters[256] = {0};
	unsigned char letter = 0;
	unsigned char previous = 0;
	int character_amount = 0;
        while (!file -> eof()) {
            characters[letter]++;
            double_characters[previous][letter]++;

            // get the next character
            previous = letter;
            letter = file -> get();

            character_amount++;
        }

	double HYX = 0;
	for(int x = 0; x < 256; x++) {
		for(int y = 0; y < 256; y++) {
			if(characters[x] != 0 && double_characters[x][y] != 0) {
				double pxy = double_characters[x][y] / (double) character_amount;
				double logpxypx = std::log2(((double) double_characters[x][y]) / ((double) characters[x]));
				HYX += pxy * logpxypx;
			}
		}
	}

	if(HYX == 0) {
		return HYX;
	}

	return -1 * HYX;
}

double abs(double x) {
	if(x < 0) {
		return -1 * x;
	}

	return x;
}

int main(int argc, char* argv[]) {
	if(argc < 2) {
		std::cout << "Add filename argument\n";
		return 1;
	}
	std::ifstream file(argv[1], std::ios::in | std::ios::binary);
	if(!file.is_open()) {
		std::cerr << "Could not open the file '" << argv[1] << "'" << std::endl;
		return 1;
	}

	double entropy = calculate_entropy(&file);
	std::cout << "Entropy = " << entropy << std::endl;

	std::ifstream file2(argv[1], std::ios::in | std::ios::binary);
	if(!file2.is_open()) {
		std::cerr << "Could not open the file '" << argv[1] << "'" << std::endl;
		return 1;
	}

	double conditional_entropy = calculate_conditional_entropy(&file2);
	std::cout << "Conditional entropy = " << conditional_entropy << std::endl;
	std::cout << "Difference between entropy and conditional entropy = " << abs(entropy - conditional_entropy) << std::endl;
}
