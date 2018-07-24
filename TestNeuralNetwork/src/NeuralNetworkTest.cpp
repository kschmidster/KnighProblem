#include "NeuralNetworkTest.h"
#include "cute.h"

#include "NeuralNetwork.h"

void neuralNetworkDefaultConstructible() {
	ASSERT(std::is_default_constructible<nn::NeuralNetwork>::value);
}

cute::suite make_suite_NeuralNetworkTest() {
	cute::suite s { };
	s.push_back(CUTE(neuralNetworkDefaultConstructible));
	return s;
}
