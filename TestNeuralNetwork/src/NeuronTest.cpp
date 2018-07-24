#include "NeuronTest.h"
#include "cute.h"

#include "Neuron.h"

#include <type_traits>

void inputNeuronDefaultConstructible() {
	ASSERT(std::is_default_constructible<nn::InputNeuron>::value);
}

void outputNeuronDefaultConstructible() {
	ASSERT(std::is_default_constructible<nn::OutputNeuron>::value);
}

void hiddenNeuronDefaultConstructible() {
	ASSERT(std::is_default_constructible<nn::HiddenNeuron<>>::value);
}

cute::suite make_suite_NeuronTest() {
	cute::suite s { };
	s.push_back(CUTE(inputNeuronDefaultConstructible));
	s.push_back(CUTE(outputNeuronDefaultConstructible));
	s.push_back(CUTE(hiddenNeuronDefaultConstructible));
	return s;
}
