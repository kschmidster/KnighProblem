#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include "Layer.h"

#include <vector>

namespace nn { /* namespace neural network */

struct NeuralNetwork {
private:
	InputLayer inputLayer { };
	std::vector<HiddenLayer> hiddenLayers { };
	OutputLayer outputLayer { };
};

} /* end namespace neural network */

#endif /* NEURALNETWORK_H_ */
