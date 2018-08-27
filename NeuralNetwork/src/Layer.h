#ifndef LAYER_H_
#define LAYER_H_

#include "Neuron.h"

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <functional>

namespace nn { /* namespace neural network */

namespace layer { /* namespace layer */

struct Layer {
	using const_neurons = std::vector<Neuron> const&;

	Layer() = default;
	explicit Layer(size_t const neurons) :
			neurons { neurons } {
	}

	void connectTo(Layer& other, std::vector<float> const& weights) {
		if (neurons.size() * other.neurons.size() != weights.size()) {
			throw std::invalid_argument { "Weights do not match the amount of connections" };
		}
		size_t weightIndex { }; // TODO I do not like that
		std::for_each(neurons.begin(), neurons.end(), [&](Neuron& from) {
			for_each(other.neurons.begin(), other.neurons.end(), [&](Neuron& to) {
						from.connectTo(to, weights.at(weightIndex++));
					});
		});
	}
	void connectTo(Layer& other) {
		connectTo(other, std::vector<float>(neurons.size() * other.neurons.size()));
	}

	void randomizeWeights() {
		lambda function = [](Neuron &neuron) { neuron.randomizeWeights(); };
		applyOnNeurons(function);
	}

	void clearInputs() {
		lambda function = [](Neuron &neuron){ neuron.clearInput(); };
		applyOnNeurons(function);
	}
	void processInputs() {
		std::for_each(neurons.begin(), neurons.end(), [](Neuron &neuron) {
			neuron.processInput();
		});
	}

	const_neurons getNeurons() const {
		return neurons;
	}

protected:
	using lambda = std::function<void (Neuron&)>;

	void applyOnNeurons(lambda &function) {
		std::for_each(neurons.begin(), neurons.end(), function);
	}
	
	std::vector<Neuron> neurons { };
};

} /* end namespace layer */

// Convenience types for type safety
using layer::Layer;

struct InputLayer: Layer {
	using Layer::Layer;

	void setInputs(std::vector<double> const& inputs) {
		std::for_each(inputs.begin(), inputs.end(), [&](double input) {
			std::for_each(neurons.begin(), neurons.end(), [&input](Neuron &neuron) {
						neuron.setInput(input);
					});
		});
	}
};

struct HiddenLayer: Layer {
	using Layer::Layer;
};

struct OutputLayer: Layer {
	using Layer::Layer;

	std::vector<double> getOutputs() const {
		std::vector<double> outputs {  };
		std::for_each(neurons.begin(), neurons.end(), [&outputs](Neuron const& neuron) {
			outputs.push_back(neuron.getValue());
		});
		return outputs;
	}
};

} /* end namespace neural network */

#endif /* LAYER_H_ */
