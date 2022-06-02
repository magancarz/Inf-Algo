#include <fstream>
#include <cstring>
#include <cmath>
#include "TGAImage.h"
#include "Encoder.h"
#include "Decoder.h"

int main(int argc, char** argv) {
	if(strcmp(argv[1], "encode") == 0) {
		std::ifstream input(argv[2]);
		std::ofstream output(argv[3]);
		int bitsNumber = strtol(argv[4], nullptr, 10);

		Encoder encoder = Encoder(TGAImage(input));
		encoder.createFilters();
		encoder.createDictionaries(bitsNumber);
		encoder.writeDictionaryToFile(output, bitsNumber);
		encoder.writeHeaderToFile(output);
		encoder.writeCodeToFile(output);

		input.close();
		output.close();
	} else if(strcmp(argv[1], "decode") == 0) {
		std::ifstream input(argv[2]);
		std::ofstream output(argv[3]);
		
		Decoder decoder = Decoder();
		decoder.getDictionary(input);

		decoder.writeHeaderToFile(input, output);
		decoder.writePixelsToFile(input, output);

		input.close();
		output.close();
	} else if(strcmp(argv[1], "compare") == 0) {
		std::ifstream original(argv[2]);
		std::ifstream copy(argv[3]);

	    Encoder eoriginal = Encoder(TGAImage(original));
	    Encoder ecopy = Encoder(TGAImage(copy));

	    const std::vector<Pixel>& originalImage = eoriginal.getImage().getImage();
	    const std::vector<Pixel>& newImage = ecopy.getImage().getImage();
	    int size = originalImage.size();
	    uint64_t valueToRedMse = 0;
	    uint64_t valueToGreenMse = 0;
	    uint64_t valueToBlueMse = 0;
	    uint64_t valueToSnr = 0;

	    for (int i = 0; i < size; i++) {
			valueToRedMse += pow(originalImage[i].red - newImage[i].red, 2);
			valueToGreenMse += pow(originalImage[i].green - newImage[i].green, 2);
			valueToBlueMse += pow(originalImage[i].blue - newImage[i].blue, 2);

			valueToSnr += originalImage[i].red * newImage[i].red +
				originalImage[i].green * newImage[i].green +
				originalImage[i].blue * newImage[i].blue;
	    }

	    double mseRed = double(valueToRedMse) / (size);
	    double mseGreen = double(valueToGreenMse) / (size);
	    double mseBlue = double(valueToBlueMse) / (size);
	    double mse = (mseRed + mseGreen + mseBlue) / 3;
	    double snr = (double(valueToSnr) / (size * 3)) / mse;

	    printf("MSE = %f\n", mse);
	    printf("MSE (r) = %f\n", mseRed);
	    printf("MSE (g) = %f\n", mseGreen);
	    printf("MSE (b) = %f\n", mseBlue);
	    printf("SNR = %f (%fdB)\n", snr, 10 * log10(snr));

	    original.close();
	    copy.close();
	}
    
    return 0;
}
