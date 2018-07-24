#ifndef NEURON_H_
#define NEURON_H_

#include "Connection.h"

#include <vector>
#include <memory>

namespace nn { /* namespace neural network */

template<typename T>
struct Connection; // forward declaration

namespace neuron { /* namespace neuron */

template<typename NEURON>
struct NeuronImpl {
	NeuronImpl& operator*() { return *this; }
	NeuronImpl const& operator*() const { return *this; }
private:
	std::vector<Connection<NEURON>> connections { };
};

template<typename KIND>
struct Neuron {
	Neuron() : neuron { std::make_shared<KIND>() } { }
protected:
	std::shared_ptr<KIND> neuron { };
};

template<typename INPUT, typename OUTPUT>
struct HiddenNeuronImpl {
	HiddenNeuronImpl& operator*() { return *this; }
	HiddenNeuronImpl const& operator*() const { return *this; }
private:
	std::vector<Connection<INPUT>> inputConnections { };
	std::vector<Connection<OUTPUT>> outputConnections { };
};

} /* end namespace neuron */

struct InputNeuron : neuron::Neuron<nn::neuron::NeuronImpl<InputNeuron>> {
	using Neuron::Neuron;
};

struct OutputNeuron : neuron::Neuron<nn::neuron::NeuronImpl<OutputNeuron>> {
	using Neuron::Neuron;
};

template<typename INPUT = InputNeuron, typename OUTPUT = OutputNeuron>
struct HiddenNeuron {
	using hiddenNeuron = HiddenNeuron<INPUT, OUTPUT>;
	HiddenNeuron() : neuron { std::make_shared<hiddenNeuron>() } { }
protected:
	std::shared_ptr<hiddenNeuron> neuron { };
};

} /* end namespace neural network */

#endif /* NEURON_H_ */
