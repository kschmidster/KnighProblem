#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include "Layer.h"

#include <vector>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <stdlib.h>

namespace nn { /* namespace neural network */

namespace lv { /* namespace layer validator */

struct LayerValidator {
	bool operator()(InputLayer const& inputLayer, OutputLayer const& outputLayer) const {
		return validateLayer(inputLayer) && validateLayer(outputLayer);
	}
	bool validateLayer(Layer const& layer) const {
		return not layer.getNeurons().empty();
	}
};

} /* namespace layer validator */

const auto validateLayer = lv::LayerValidator { };

struct NeuralNetwork {
	using const_ref_inputLayer = InputLayer const&;
	using const_ref_hiddenLayer = std::vector<HiddenLayer> const&;
	using const_ref_outputLayer = OutputLayer const&;

	// TODO maybe connection strategy
	// consider bias

	NeuralNetwork() = default;
	NeuralNetwork(InputLayer&& inputLayer, OutputLayer&& outputLayer, std::vector<HiddenLayer>&& hiddenLayers = std::vector<HiddenLayer> { }) :
			inputLayer { std::forward<InputLayer>(inputLayer) }, outputLayer { std::forward<OutputLayer>(outputLayer) }, hiddenLayers { std::forward<
					std::vector<HiddenLayer>>(hiddenLayers) } {
		if (not validateLayer(this->inputLayer, this->outputLayer)) {
			throw std::invalid_argument { "Passed Layers are not valid" };
		}
		connectLayers();
		// TODO okay for the moment, but maybe init from file
		randomizeWeights();
	}

	template<typename T>
	void setInputs(std::vector<T> const& inputs) {
		inputLayer.setInputs(inputs);
	}
	const std::vector<double> getOutputs() {
		clearInputsInHiddenAndOutputLayers();
		processInputs();
		return outputLayer.getOutputs();
	}

	template<typename T>
	void trainNetwork(std::vector<T> const& inputs, std::vector<double> const& shouldOutputs) {
		// TODO implement
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

	void randomizeWeights() {
		inputLayer.randomizeWeights();

		if (!hiddenLayers.empty()) {
			std::for_each(hiddenLayers.begin(), hiddenLayers.end(), [](HiddenLayer &hiddenLayer) {
				hiddenLayer.randomizeWeights();
			});
		}
	}

	void clearInputsInHiddenAndOutputLayers() {
		std::for_each(hiddenLayers.begin(), hiddenLayers.end(), [](Layer &layer) {
			layer.clearInputs();
		});
		outputLayer.clearInputs();
	}
	void processInputs() {
		inputLayer.processInputs();
		std::for_each(hiddenLayers.begin(), hiddenLayers.end(), [](Layer &layer) {
			layer.processInputs();
		});
		outputLayer.processInputs();
	}

	InputLayer inputLayer { };
	OutputLayer outputLayer { };
	// may not used
	std::vector<HiddenLayer> hiddenLayers { };
};

} /* end namespace neural network */

#endif /* NEURALNETWORK_H_ */
