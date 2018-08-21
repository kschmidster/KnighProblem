#include "NeuralNetworkBuilderTest.h"
#include "cute.h"

#include "NeuralNetworkBuilder.h"
#include "TestHelper.h"

using nn::test::testNeuronalNetwork;

void neuralNetworkConstuctsItselfCorrectlyWithBuilderWithoutHiddenLayer() {
	nn::NeuralNetwork const nn = nn::NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(1) //
	.withOutputLayerNeuronsCount(1) //
	.build();

	testNeuronalNetwork(nn);
}

void neuralNetworkConstuctsItselfCorrectlyWithBuilder() {
	nn::NeuralNetwork const nn = nn::NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(1) //
	.withHiddenLayerNeuronCount(1) //
	.withOutputLayerNeuronsCount(1) //
	.build();

	testNeuronalNetwork(nn);
}

void neuralNetworkConstuctsItselfCorrectlyWithBuilderComplexWithoutHiddenLayer() {
	nn::NeuralNetwork const nn = nn::NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(9) //
	.withOutputLayerNeuronsCount(9) //
	.build();

	testNeuronalNetwork(nn);
}

void neuralNetworkConstuctsItselfCorrectlyWithBuilderComplex() {
	nn::NeuralNetwork const nn = nn::NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(9) //
	.withHiddenLayerNeuronCount(9) //
	.withOutputLayerNeuronsCount(9) //
	.build();

	testNeuronalNetwork(nn);
}

void neuralAsyncNetworkConstuctsItselfCorrectlyWithBuilderWithoutHiddenLayer() {
	nn::NeuralNetwork const nn = nn::NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(1) //
	.withOutputLayerNeuronsCount(2) //
	.build();

	testNeuronalNetwork(nn);
}

void neuralAsyncNetworkConstuctsItselfCorrectlyWithBuilderWithHiddenLayer() {
	nn::NeuralNetwork const nn = nn::NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(1) //
	.withHiddenLayerNeuronCount(2) //
	.withOutputLayerNeuronsCount(3) //
	.build();

	testNeuronalNetwork(nn);
}

void neuralAsyncNetworkConstuctsItselfCorrectlyWithBuilderWithMultipleHiddenLayer() {
	nn::NeuralNetwork const nn = nn::NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(1) //
	.withHiddenLayerNeuronCount(2) //
	.withHiddenLayerNeuronCount(4) //
	.withOutputLayerNeuronsCount(5) //
	.build();

	testNeuronalNetwork(nn);
}

void tryConstructNeuralNetworkWithInvalidInputLayerWithBuilder() {
	nn::NeuralNetworkBuilder builder = nn::NeuralNetworkBuilder().withOutputLayerNeuronsCount(1);
	ASSERT_THROWS(builder.build(), std::logic_error);
}

void tryConstructNeuralNetworkWithInvalidOutputLayerWithBuilder() {
	nn::NeuralNetworkBuilder builder = nn::NeuralNetworkBuilder().withInputLayerNeuronsCount(1);
	ASSERT_THROWS(builder.build(), std::logic_error);
}

cute::suite make_suite_NeuralNetworkBuilderTest() {
	cute::suite s { };
	s.push_back(CUTE(neuralNetworkConstuctsItselfCorrectlyWithBuilderWithoutHiddenLayer));
	s.push_back(CUTE(neuralNetworkConstuctsItselfCorrectlyWithBuilderComplexWithoutHiddenLayer));
	s.push_back(CUTE(neuralNetworkConstuctsItselfCorrectlyWithBuilder));
	s.push_back(CUTE(neuralNetworkConstuctsItselfCorrectlyWithBuilderComplex));
	s.push_back(CUTE(neuralAsyncNetworkConstuctsItselfCorrectlyWithBuilderWithoutHiddenLayer));
	s.push_back(CUTE(neuralAsyncNetworkConstuctsItselfCorrectlyWithBuilderWithHiddenLayer));
	s.push_back(CUTE(neuralAsyncNetworkConstuctsItselfCorrectlyWithBuilderWithMultipleHiddenLayer));
	s.push_back(CUTE(tryConstructNeuralNetworkWithInvalidInputLayerWithBuilder));
	s.push_back(CUTE(tryConstructNeuralNetworkWithInvalidOutputLayerWithBuilder));
	return s;
}
