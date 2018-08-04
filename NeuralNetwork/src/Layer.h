#ifndef LAYER_H_
#define LAYER_H_

#include "Neuron.h"

#include <vector>
#include <algorithm>

namespace nn { /* namespace neural network */

namespace layer { /* namespace layer */

struct Layer {
	using const_neurons = std::vector<Neuron> const&;

	Layer() = default;
	explicit Layer(size_t const neurons) :
			neurons { neurons } {
	}

	void connectTo(Layer& other) {
		std::for_each(neurons.begin(), neurons.end(), [&](Neuron& from) {
			for_each(other.neurons.begin(), other.neurons.end(), [&](Neuron& to) {
				from.connectTo(to);
			});
		});
	}

	const_neurons getNeurons() const {
		return neurons;
	}
	std::vector<Neuron>& getNeurons() {
		return neurons;
	}

private:
	std::vector<Neuron> neurons { };
};

} /* end namespace layer */

// Convinience types for type safety
using layer::Layer;

struct InputLayer: Layer {
	using Layer::Layer;
};

struct HiddenLayer: Layer {
	using Layer::Layer;
};

struct OutputLayer: Layer {
	using Layer::Layer;
};

} /* end namespace neural network */

#endif /* LAYER_H_ */
