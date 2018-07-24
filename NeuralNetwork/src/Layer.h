#ifndef LAYER_H_
#define LAYER_H_

#include "Neuron.h"

#include <vector>

namespace nn { /* namespace neural network */

namespace layer { /* namespace layer */

template<typename NEURON>
struct Layer {
	Layer() = default;
	explicit Layer(const int neurons) :
			neurons(neurons) {
	}
private:
	std::vector<NEURON> neurons { };
};

} /* end namespace layer */

struct InputLayer: layer::Layer<InputNeuron> {
	using Layer::Layer;
};

struct OutputLayer: layer::Layer<OutputNeuron> {
	using Layer::Layer;
};

template<typename INPUT = InputNeuron, typename OUTPUT = OutputNeuron>
struct HiddenLayer {
	HiddenLayer() = default;
	HiddenLayer(const int inputNeurons, const int outputNeurons) :
			inputNeurons(inputNeurons), outputNeurons(outputNeurons) {
	}
private:
	std::vector<INPUT> inputNeurons { };
	std::vector<OUTPUT> outputNeurons { };
};

} /* end namespace neural network */

#endif /* LAYER_H_ */
