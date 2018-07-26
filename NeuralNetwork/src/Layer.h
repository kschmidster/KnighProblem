#ifndef LAYER_H_
#define LAYER_H_

#include "Neuron.h"

#include <vector>

namespace nn { /* namespace neural network */

namespace layer { /* namespace layer */

struct Layer {
	Layer() = default;
	explicit Layer(size_t neurons) :
			neurons(neurons) {
	}
private:
	std::vector<nn::Neuron> neurons { };
};

} /* end namespace layer */

// Convinience types for type safety
using layer::Layer;

struct InputLayer : Layer {
	using Layer::Layer;
};

struct HiddenLayer : Layer {
	using Layer::Layer;
};

struct OutputLayer : Layer {
	using Layer::Layer;
};

} /* end namespace neural network */

#endif /* LAYER_H_ */
