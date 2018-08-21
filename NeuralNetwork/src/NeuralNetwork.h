#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include "Layer.h"

#include <vector>
#include <utility>
#include <stdexcept>

namespace nn { /* namespace neural network */

namespace lv { /* namespace lv */

struct LayerValidator {
	bool operator()(InputLayer const& inputLayer, OutputLayer const& outputLayer) const {
		return validateLayer(inputLayer) && validateLayer(outputLayer);
	}
	bool validateLayer(Layer const& layer) const {
		return not layer.getNeurons().empty();
	}
};

} /* namespace lv */

const auto validateLayer = lv::LayerValidator { };

struct NeuralNetwork {
	using const_ref_inputLayer = InputLayer const&;
	using const_ref_hiddenLayer = std::vector<HiddenLayer> const&;
	using const_ref_outputLayer = OutputLayer const&;

	NeuralNetwork() = default;
	NeuralNetwork(InputLayer&& inputLayer, OutputLayer&& outputLayer, std::vector<HiddenLayer>&& hiddenLayers = std::vector<HiddenLayer> { }) :
			inputLayer { std::forward<InputLayer>(inputLayer) }, outputLayer { std::forward<OutputLayer>(outputLayer) }, hiddenLayers { std::forward<
					std::vector<HiddenLayer>>(hiddenLayers) } {
		if (not validateLayer(this->inputLayer, this->outputLayer)) {
			throw std::invalid_argument { "Passed Layers are not valid" };
		}
		connectLayers();
	}

	const_ref_inputLayer getInputLayer() const {
		return inputLayer;
	}
	const_ref_hiddenLayer getHiddenLayers() const {
		return hiddenLayers;
	}
	const_ref_outputLayer getOutputLayer() const {
		return outputLayer;
	}

private:
	void connectLayers() {
		if (hiddenLayers.empty()) {
			inputLayer.connectTo(outputLayer);
		} else {
			connectAllLayers();
		}
	}
	void connectAllLayers() {
		inputLayer.connectTo(hiddenLayers.at(0));
		// TODO ugly code, don't look at it :P, have to find a good std algorithm
		for (auto i = hiddenLayers.begin(); i != hiddenLayers.end() - 1; i++) {
			(*i).connectTo(*(i + 1));
		}
		hiddenLayers.at(hiddenLayers.size() - 1).connectTo(outputLayer);
	}

	InputLayer inputLayer { };
	OutputLayer outputLayer { };
	// may not used
	std::vector<HiddenLayer> hiddenLayers { };
};

} /* end namespace neural network */

#endif /* NEURALNETWORK_H_ */
