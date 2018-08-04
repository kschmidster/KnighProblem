#include "NeuronTest.h"
#include "cute.h"

#include "Neuron.h"

#include <type_traits>

using nn::Neuron;

void neuronDefaulConstructible() {
	ASSERT(std::is_default_constructible<Neuron>::value);
}

void neuronCopyConstructible() {
	ASSERT(std::is_copy_constructible<Neuron>::value);
}

void neuronCopyAssignable() {
	ASSERT(std::is_copy_assignable<Neuron>::value);
}

void neuronOnHeapDefaulConstructible() {
	ASSERT(std::is_default_constructible<nn::neuron::Neuron<size_t>>::value);
}

void neuronNotCopyConstructible() {
	ASSERT(not std::is_copy_constructible<nn::neuron::Neuron<size_t>>::value);
}

void neuronNotCopyAssignable() {
	ASSERT(not std::is_copy_assignable<nn::neuron::Neuron<size_t>>::value);
}

void connectTwoDifferentNeurons() {
	using namespace nn;
	Neuron n1 { };
	Neuron n2 { };
	n1.connectTo(n2);

	ASSERT_EQUAL(1, n1.getOutConnections().size());
	ASSERT_EQUAL(0, n1.getInConnections().size());
	ASSERT_EQUAL(0, n2.getOutConnections().size());
	ASSERT_EQUAL(1, n2.getInConnections().size());
}

void connectSameNeurons() {
	using namespace nn;
	Neuron n1 { };
	n1.connectTo(n1);

	ASSERT_EQUAL(1, n1.getOutConnections().size());
	ASSERT_EQUAL(1, n1.getInConnections().size());
}

cute::suite make_suite_NeuronTest() {
	cute::suite s { };
	s.push_back(CUTE(neuronDefaulConstructible));
	s.push_back(CUTE(neuronCopyConstructible));
	s.push_back(CUTE(neuronCopyAssignable));
	s.push_back(CUTE(neuronOnHeapDefaulConstructible));
	s.push_back(CUTE(neuronNotCopyConstructible));
	s.push_back(CUTE(neuronNotCopyAssignable));
	s.push_back(CUTE(connectTwoDifferentNeurons));
	s.push_back(CUTE(connectSameNeurons));
	return s;
}
