#include "mnistFileParser.h"

#include "NeuralNetwork.h"
#include "NeuralNetworkBuilder.h"

#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <stdexcept>

namespace testnn { /* namespace test neural network */

constexpr uint32_t NUMBER_OF_LABELS { 10 };
const std::vector<double> ZERO { 1., 0., 0., 0., 0., 0., 0., 0., 0., 0. };
const std::vector<double> ONE { 0., 1., 0., 0., 0., 0., 0., 0., 0., 0. };
const std::vector<double> TWO { 0., 0., 1., 0., 0., 0., 0., 0., 0., 0. };
const std::vector<double> THREE { 0., 0., 0., 1., 0., 0., 0., 0., 0., 0. };
const std::vector<double> FOUR { 0., 0., 0., 0., 1., 0., 0., 0., 0., 0. };
const std::vector<double> FIVE { 0., 0., 0., 0., 0., 1., 0., 0., 0., 0. };
const std::vector<double> SIX { 0., 0., 0., 0., 0., 0., 1., 0., 0., 0. };
const std::vector<double> SEVEN { 0., 0., 0., 0., 0., 0., 0., 1., 0., 0. };
const std::vector<double> EIGHT { 0., 0., 0., 0., 0., 0., 0., 0., 1., 0. };
const std::vector<double> NINE { 0., 0., 0., 0., 0., 0., 0., 0., 0., 1. };

auto createNeuralNetworkForImages(uint32_t const inputs, uint32_t const outputs = NUMBER_OF_LABELS) {
	return nn::NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(inputs) //
	.withHiddenLayerNeuronCount(inputs / 2) //
	.withOutputLayerNeuronsCount(outputs) //
	.build();
}

const std::vector<double> createShouldOutputs(int const output) {
	switch (output) {
	case 0:
		return ZERO;
	case 1:
		return ONE;
	case 2:
		return TWO;
	case 3:
		return THREE;
	case 4:
		return FOUR;
	case 5:
		return FIVE;
	case 6:
		return SIX;
	case 7:
		return SEVEN;
	case 8:
		return EIGHT;
	case 9:
		return NINE;
	default:
		throw std::invalid_argument { "Not defined" };
	}
}

void trainNeuralNetworkWithImages(nn::NeuralNetwork &nn, std::vector<std::pair<int, std::vector<char>>> imagesWithLabel) {
	std::for_each(imagesWithLabel.begin(), imagesWithLabel.end(), [&nn](auto const& entry) {
		nn.trainNetwork(entry.second, createShouldOutputs(entry.first));
	});
}

} /* end namespace test neural network */

int main() {
	auto const imagesWithLabel = mnist::readImagesFromFiles(std::cout);
	auto nn = testnn::createNeuralNetworkForImages(imagesWithLabel.at(0).second.size());
	testnn::trainNeuralNetworkWithImages(nn, imagesWithLabel);
}
