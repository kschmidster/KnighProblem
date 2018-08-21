#ifndef NEURALNETWORKBUILDER_H_
#define NEURALNETWORKBUILDER_H_

#include "NeuralNetwork.h"
#include "Layer.h"

#include <vector>
#include <utility>
#include <stdexcept>

namespace nn { /* namespace nn */

struct NeuralNetworkBuilder {
	using reference = NeuralNetworkBuilder&;

	reference withInputLayerNeuronsCount(size_t const neurons) {
		inputLayer = InputLayer { neurons };
		return *this;
	}
	reference withHiddenLayerNeuronCount(size_t const neurons) {
		hiddenLayers.push_back(HiddenLayer { neurons });
		return *this;
	}
	reference withOutputLayerNeuronsCount(size_t const neurons) {
		outputLayer = OutputLayer { neurons };
		return *this;
	}
	NeuralNetwork build() {
		if (not validateLayer(inputLayer, outputLayer)) {
			throw std::logic_error { "At least one of the layers has not been constructed" };
		}
		return NeuralNetwork(std::move(inputLayer), std::move(outputLayer), std::move(hiddenLayers));
	}

	InputLayer inputLayer { };
	OutputLayer outputLayer { };
	std::vector<HiddenLayer> hiddenLayers { };
};

} /* end namespace nn */

#endif /* NEURALNETWORKBUILDER_H_ */
