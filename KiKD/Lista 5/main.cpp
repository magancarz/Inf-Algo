#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <iostream>
#include <cstdint>
#include <string>

struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    bool theSameValues(Pixel p) {
        return this->red == p.red && this->green == p.green && this->blue == p.blue;
    }
};

struct Node;

class DictionaryTree {
public:
    DictionaryTree(std::vector<std::vector<Pixel>>& image, int size);
    Pixel getNewPixel(Pixel pixel);
    static int distance(Pixel p1, Pixel p2);

private:
    void createNode(const std::vector<Pixel>& pixels, Node* node);
    void setAverageDistance(Node* node, std::vector<Pixel>& pixels);

    Node* root;
    int height;
};

struct Node {
    std::string code;
    Pixel pixel;
    Node* left;
    Node* right;
};

DictionaryTree::DictionaryTree(std::vector<std::vector<Pixel>>& image, int size) {
    this->root = new Node{"", Pixel(), nullptr, nullptr};
    this->height = size;

	int heightImage = image.size();
    int widthImage = image[0].size();

    std::vector<Pixel> pixels(widthImage * heightImage);

    for (int i = 0; i < heightImage; i++) {
        for (int j = 0; j < widthImage; j++) {
            pixels[i * widthImage + j] = image[i][j];
        }
    }

    this->setAverageDistance(this->root, pixels);
    this->createNode(pixels, this->root);
}

Pixel DictionaryTree::getNewPixel(Pixel pixel) {
    Node* node = this->root;

    while (node->left != nullptr) {
        if (DictionaryTree::distance(pixel, node->left->pixel) < DictionaryTree::distance(pixel, node->right->pixel)) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return node->pixel;
}

int DictionaryTree::distance(Pixel p1, Pixel p2) {
    return abs(p1.red - p2.red) + abs(p1.green - p2.green) + abs(p1.blue - p2.blue);
}

void DictionaryTree::createNode(const std::vector<Pixel>& pixels, Node* node) {
    if (node->code.size() == this->height)
        return;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> randInt(-3, 3);

    node->left = new Node{node->code + "0", node->pixel, nullptr, nullptr};
    node->right = new Node{node->code + "1", node->pixel, nullptr, nullptr};
	
    do {
        node->right->pixel.red = std::max(0, std::min(255, (int) node->right->pixel.red + randInt(generator)));
        node->right->pixel.green = std::max(0, std::min(255, (int) node->right->pixel.green + randInt(generator)));
        node->right->pixel.blue = std::max(0, std::min(255, (int) node->right->pixel.blue + randInt(generator)));
    } while (node->left->pixel.red == node->right->pixel.red
    && node->left->pixel.green == node->right->pixel.green
    && node->left->pixel.blue == node->right->pixel.blue);

    std::vector<Pixel> pixelsLeft;
    std::vector<Pixel> pixelsRight;

    Pixel pixelLeftPrev;
    Pixel pixelRightPrev;

    do {
        pixelLeftPrev = node->left->pixel;
        pixelRightPrev = node->right->pixel;

        pixelsLeft.clear();
        pixelsRight.clear();

        for (Pixel pixel : pixels) {
            if (DictionaryTree::distance(pixel, node->left->pixel) <
                DictionaryTree::distance(pixel, node->right->pixel)) {
                pixelsLeft.push_back(pixel);
            } else {
                pixelsRight.push_back(pixel);
            }
        }

        DictionaryTree::setAverageDistance(node->left, pixelsLeft);
        DictionaryTree::setAverageDistance(node->right, pixelsRight);
    } while (!(node->left->pixel.theSameValues(pixelLeftPrev) && node->right->pixel.theSameValues(pixelRightPrev)));

    this->createNode(pixelsLeft, node->left);
    this->createNode(pixelsRight, node->right);
}

void DictionaryTree::setAverageDistance(Node* node, std::vector<Pixel> &pixels) {
    uint64_t red = 0;
    uint64_t green = 0;
    uint64_t blue = 0;
    int pixelAmount = pixels.size();

    for (Pixel p : pixels) {
        red += p.red;
        green += p.green;
        blue += p.blue;
    }

    if (pixelAmount > 0) {
        node->pixel.red = red / pixelAmount;
        node->pixel.green = green / pixelAmount;
        node->pixel.blue = blue / pixelAmount;
    }
}


#pragma pack(push, 1)

struct TGAHeader {
    uint8_t idLength;
    uint8_t colorMapType;
    uint8_t imageType;

    uint16_t colorMapEntryIndex;
    uint16_t colorMapLength;
    uint8_t colorMapSize;

    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint8_t pixelBits;
    uint8_t descriptor;
};
#pragma pack(pop)

std::vector<std::vector<Pixel> > getImage(std::ifstream& dataFile, TGAHeader tgaHeader);

int main(int argc, char** argv) {

	std::ifstream dataFile(argv[1]);
	std::ofstream answerFile(argv[2]);
	int colorNumber = (int) strtol(argv[3], nullptr, 10);
	
    TGAHeader header{};
    dataFile.read(reinterpret_cast<char *>(&header), sizeof(TGAHeader));

    std::vector<std::vector<Pixel>> image = getImage(dataFile, header);
    DictionaryTree dict(image, colorNumber);

    answerFile.write((char*)&header, sizeof(TGAHeader));
    uint64_t valueToMse = 0;
    uint64_t valueToSnr = 0;

    for (int i = 0; i < header.height; i++) {
        for (int j = 0; j < header.width; j++) {
            Pixel pixel = dict.getNewPixel(image[i][j]);
            answerFile << pixel.red;
            answerFile << pixel.green;
            answerFile << pixel.blue;
            valueToMse += DictionaryTree::distance(image[i][j], pixel);
            valueToSnr += pixel.red * pixel.red + pixel.green * pixel.green + pixel.blue * pixel.blue;
        }
    }

    dataFile.close();
    answerFile.close();

    double mse = double(valueToMse) / (header.height * header.width);
    double snr = (double(valueToSnr) / ((header.height * header.width))) / mse;
    printf("Mean Square Error = %f\n", mse);
    printf("Signal-To-Noise Ratio = %f (%fdB)\n", snr, 10 * log10(snr));
}

std::vector<std::vector<Pixel> > getImage(std::ifstream& dataFile, TGAHeader tgaHeader) {
    std::vector<std::vector<Pixel> > image(tgaHeader.height, std::vector<Pixel>(tgaHeader.width));

    for (int i = 0; i < tgaHeader.height; i++) {
        for (int j = 0; j < tgaHeader.width; j++) {
            dataFile >> std::noskipws >> image[i][j].red;
            dataFile >> std::noskipws >> image[i][j].green;
            dataFile >> std::noskipws >> image[i][j].blue;
        }
    }

    return image;
}
