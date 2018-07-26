#include "NeuralNetworkTest.h"
#include "cute.h"

#include "NeuralNetwork.h"

void neuralNetworkDefaultConstructible() {
	ASSERT(std::is_default_constructible<nn::NeuralNetwork>::value);
}

void neuralNetworkCopyConstructible() {
	ASSERT(std::is_copy_constructible<nn::NeuralNetwork>::value);
}

void neuralNetworkCopyAssignable() {
	ASSERT(std::is_copy_assignable<nn::NeuralNetwork>::value);
}

cute::suite make_suite_NeuralNetworkTest() {
	cute::suite s { };
	s.push_back(CUTE(neuralNetworkDefaultConstructible));
	s.push_back(CUTE(neuralNetworkCopyConstructible));
	s.push_back(CUTE(neuralNetworkCopyAssignable));
	return s;
}
