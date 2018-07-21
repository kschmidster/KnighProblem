#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include "Layer.h"

namespace nn { /* namespace neural network */

struct NeuralNetwork {
private:
	InputLayer inputLayer { };
	HiddenLayer<> hiddenLayer { };
	OutputLayer outputLayer { };
};

} /* end namespace neural network */

#endif /* NEURALNETWORK_H_ */
