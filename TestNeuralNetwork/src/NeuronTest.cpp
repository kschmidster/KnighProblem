#include "NeuronTest.h"
#include "cute.h"

#include "Neuron.h"

#include <type_traits>

void neuronDefaulConstructible() {
	ASSERT(std::is_default_constructible<nn::Neuron>::value);
}

void neuronCopyConstructible() {
	ASSERT(std::is_copy_constructible<nn::Neuron>::value);
}

void neuronCopyAssignable() {
	ASSERT(std::is_copy_assignable<nn::Neuron>::value);
}


cute::suite make_suite_NeuronTest() {
	cute::suite s { };
	s.push_back(CUTE(neuronDefaulConstructible));
	s.push_back(CUTE(neuronCopyConstructible));
	s.push_back(CUTE(neuronCopyAssignable));
	return s;
}
