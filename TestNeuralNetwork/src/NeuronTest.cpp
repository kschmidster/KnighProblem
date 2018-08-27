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
	ASSERT_EQUAL(0, n2.getOutConnections().size());
}

void connectSameNeurons() {
	using namespace nn;
	Neuron n1 { };
	n1.connectTo(n1);

	ASSERT_EQUAL(1, n1.getOutConnections().size());
}

void connectNeuronsWithWeight() {
	using namespace nn;
	Neuron n1 { };
	Neuron n2 { };

	float const weight { 42.f };

	n1.connectTo(n2, weight);

	ASSERT_EQUAL(weight, n1.getOutConnections().at(0).getWeight());
}

void neuronSetInput() {
	double const input { 3.0 };
	Neuron n { };

	n.setInput(input);

	ASSERT_EQUAL(input, n.getValue());
}

void neuronAddInput() {
	double const input { 3.0 };
	double const offset { 39.0 };
	Neuron n { };

	n.setInput(input);
	n.addInput(offset);

	ASSERT_EQUAL(input + offset, n.getValue());
}

void neuronClearInput() {
	Neuron n { };

	n.setInput(3.0);
	n.clearInput();

	ASSERT_EQUAL(double {}, n.getValue());
}

void neuronInputNeuronProcessInput() {
	Neuron n1 { };
	Neuron n2 { };

	n1.connectTo(n2);
	n1.setInput(42.0);
	n1.processInput();

	ASSERT_EQUAL(.0, n2.getValue());
}

void neuronInputNeuronProcessInputWithWeight() {
	Neuron n1 { };
	Neuron n2 { };

	n1.connectTo(n2, 1.0);
	n1.setInput(42.0);
	n1.processInput();

	ASSERT_EQUAL(1.0, n2.getValue());
}

void neuronInputNeuronProcessInputWithWeightDouble() {
	Neuron n1 { };
	Neuron n2 { };

	n1.connectTo(n2, 2.0);
	n1.setInput(42.0);
	n1.processInput();

	ASSERT_EQUAL(2.0, n2.getValue());
}

void neuronTestSigmoid() {
	ASSERT_EQUAL(1, nn::neuron::Neuron<size_t>::sigmoidOf(10000));
	ASSERT_EQUAL(0.5, nn::neuron::Neuron<size_t>::sigmoidOf(0));
	ASSERT_EQUAL(0, nn::neuron::Neuron<size_t>::sigmoidOf(-10000));
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
	s.push_back(CUTE(connectNeuronsWithWeight));
	s.push_back(CUTE(neuronSetInput));
	s.push_back(CUTE(neuronAddInput));
	s.push_back(CUTE(neuronClearInput));
	s.push_back(CUTE(neuronInputNeuronProcessInput));
	s.push_back(CUTE(neuronInputNeuronProcessInputWithWeight));
	s.push_back(CUTE(neuronInputNeuronProcessInputWithWeightDouble));
	s.push_back(CUTE(neuronTestSigmoid));
	return s;
}
