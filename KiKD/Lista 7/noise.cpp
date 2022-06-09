#include <bitset>
#include <random>
#include <fstream>

int main(int argc, char** argv) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> randFrom0To1(0.0, 1.0);
    
    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);
    double probability = std::stod(argv[3]);

    uint8_t byte;

    while (input >> std::noskipws >> byte) {
        std::bitset<8> currBite(byte);

        for (int i = 0; i < 8; i++) {
            if (probability >= randFrom0To1(generator))
                currBite.flip(i);
        }

        uint8_t newByte = currBite.to_ulong();
        output << newByte;
    }

    input.close();
    output.close();

    return 0;
}
