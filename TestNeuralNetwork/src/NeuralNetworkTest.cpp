#include "NeuralNetworkTest.h"
#include "cute.h"

#include "NeuralNetwork.h"
#include "Layer.h"
#include "TestHelper.h"

#include <vector>
#include <utility>
#include <stdexcept>

using nn::test::testNeuronalNetwork;
using nn::builder::NeuralNetworkBuilder;

void neuralNetworkDefaultConstructible() {
	ASSERT(std::is_default_constructible<nn::NeuralNetwork>::value);
}

void neuralNetworkCopyConstructible() {
	ASSERT(std::is_copy_constructible<nn::NeuralNetwork>::value);
}

void neuralNetworkCopyAssignable() {
	ASSERT(std::is_copy_assignable<nn::NeuralNetwork>::value);
}

void neuralNetworkConstuctsItselfCorrectlyWhenLayersArePassedWithoutHiddenLayer() {
	using namespace nn;

	InputLayer inputLayer { 1 };
	OutputLayer outputLayer { 1 };

	NeuralNetwork const nn { std::move(inputLayer), std::move(outputLayer) };

	testNeuronalNetwork(nn);
}

void neuralNetworkConstuctsItselfCorrectlyWhenLayersArePassed() {
	using namespace nn;

	InputLayer inputLayer { 1 };
	OutputLayer outputLayer { 1 };
	std::vector<HiddenLayer> hiddenLayers { HiddenLayer { 1 } };

	NeuralNetwork const nn { std::move(inputLayer), std::move(outputLayer), std::move(hiddenLayers) };

	testNeuronalNetwork(nn);
}

void neuralNetworkConstuctsItselfCorrectlyWhenLayersArePassedComplexWithoutHiddenLayer() {
	using namespace nn;

	InputLayer inputLayer { 9 };
	OutputLayer outputLayer { 9 };

	NeuralNetwork const nn { std::move(inputLayer), std::move(outputLayer) };

	testNeuronalNetwork(nn);
}

void neuralNetworkConstuctsItselfCorrectlyWhenLayersArePassedComplex() {
	using namespace nn;

	InputLayer inputLayer { 9 };
	std::vector<HiddenLayer> hiddenLayers { HiddenLayer { 9 } };
	OutputLayer outputLayer { 9 };

	NeuralNetwork const nn { std::move(inputLayer), std::move(outputLayer), std::move(hiddenLayers) };

	testNeuronalNetwork(nn);
}

void neuralNetworkAsync() {
	using namespace nn;

	InputLayer inputLayer { 3 };
	std::vector<HiddenLayer> hiddenLayers { HiddenLayer { 4 } };
	OutputLayer outputLayer { 5 };

	NeuralNetwork const nn { std::move(inputLayer), std::move(outputLayer), std::move(hiddenLayers) };

	testNeuronalNetwork(nn);
}

void neuralNetworkAsyncWithMultipleHiddenLayers() {
	using namespace nn;
	using std::move;

	InputLayer inputLayer { 3 };
	std::vector<HiddenLayer> hiddenLayers { HiddenLayer { 4 }, HiddenLayer { 5 } };
	OutputLayer outputLayer { 6 };

	NeuralNetwork const nn { move(inputLayer), move(outputLayer), move(hiddenLayers) };

	testNeuronalNetwork(nn);
}

void neuralNetworkConstuctsItselfCorrectlyWithBuilderWithoutHiddenLayer() {
	nn::NeuralNetwork const nn = NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(1) //
	.withOutputLayerNeuronsCount(1) //
	.build();

	testNeuronalNetwork(nn);
}

void neuralNetworkConstuctsItselfCorrectlyWithBuilder() {
	nn::NeuralNetwork const nn = NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(1) //
	.withHiddenLayerNeuronCount(1) //
	.withOutputLayerNeuronsCount(1) //
	.build();

	testNeuronalNetwork(nn);
}

void neuralNetworkConstuctsItselfCorrectlyWithBuilderComplexWithoutHiddenLayer() {
	nn::NeuralNetwork const nn = NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(9) //
	.withOutputLayerNeuronsCount(9) //
	.build();

	testNeuronalNetwork(nn);
}

void neuralNetworkConstuctsItselfCorrectlyWithBuilderComplex() {
	nn::NeuralNetwork const nn = NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(9) //
	.withHiddenLayerNeuronCount(9) //
	.withOutputLayerNeuronsCount(9) //
	.build();

	testNeuronalNetwork(nn);
}

void neuralAsyncNetworkConstuctsItselfCorrectlyWithBuilderWithoutHiddenLayer() {
	nn::NeuralNetwork const nn = NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(1) //
	.withOutputLayerNeuronsCount(2) //
	.build();

	testNeuronalNetwork(nn);
}

void neuralAsyncNetworkConstuctsItselfCorrectlyWithBuilderWithHiddenLayer() {
	nn::NeuralNetwork const nn = NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(1) //
	.withHiddenLayerNeuronCount(2) //
	.withOutputLayerNeuronsCount(3) //
	.build();

	testNeuronalNetwork(nn);
}

void neuralAsyncNetworkConstuctsItselfCorrectlyWithBuilderWithMultipleHiddenLayer() {
	nn::NeuralNetwork const nn = NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(1) //
	.withHiddenLayerNeuronCount(2) //
	.withHiddenLayerNeuronCount(4) //
	.withOutputLayerNeuronsCount(5) //
	.build();

	testNeuronalNetwork(nn);
}

void tryConstructNeuralNetworkWithInvalidInputLayer() {
	using namespace nn;
	ASSERT_THROWS((NeuralNetwork { InputLayer { }, OutputLayer { } }), std::invalid_argument);
}

void tryConstructNeuralNetworkWithInvalidOutputLayer() {
	using namespace nn;
	ASSERT_THROWS((NeuralNetwork { InputLayer { 1 }, OutputLayer { } }), std::invalid_argument);
}

void tryConstructNeuralNetworkWithInvalidInputLayerWithBuilder() {
	NeuralNetworkBuilder builder = NeuralNetworkBuilder().withOutputLayerNeuronsCount(1);
	ASSERT_THROWS(builder.build(), std::logic_error);
}

void tryConstructNeuralNetworkWithInvalidOutputLayerWithBuilder() {
	NeuralNetworkBuilder builder = NeuralNetworkBuilder().withInputLayerNeuronsCount(1);
	ASSERT_THROWS(builder.build(), std::logic_error);
}

cute::suite make_suite_NeuralNetworkTest() {
	cute::suite s { };
	s.push_back(CUTE(neuralNetworkDefaultConstructible));
	s.push_back(CUTE(neuralNetworkCopyConstructible));
	s.push_back(CUTE(neuralNetworkCopyAssignable));
	s.push_back(CUTE(neuralNetworkConstuctsItselfCorrectlyWhenLayersArePassedWithoutHiddenLayer));
	s.push_back(CUTE(neuralNetworkConstuctsItselfCorrectlyWhenLayersArePassed));
	s.push_back(CUTE(neuralNetworkConstuctsItselfCorrectlyWhenLayersArePassedComplexWithoutHiddenLayer));
	s.push_back(CUTE(neuralNetworkConstuctsItselfCorrectlyWhenLayersArePassedComplex));
	s.push_back(CUTE(neuralNetworkAsync));
	s.push_back(CUTE(neuralNetworkAsyncWithMultipleHiddenLayers));
	s.push_back(CUTE(neuralNetworkConstuctsItselfCorrectlyWithBuilderWithoutHiddenLayer));
	s.push_back(CUTE(neuralNetworkConstuctsItselfCorrectlyWithBuilderComplexWithoutHiddenLayer));
	s.push_back(CUTE(neuralNetworkConstuctsItselfCorrectlyWithBuilder));
	s.push_back(CUTE(neuralNetworkConstuctsItselfCorrectlyWithBuilderComplex));
	s.push_back(CUTE(neuralAsyncNetworkConstuctsItselfCorrectlyWithBuilderWithoutHiddenLayer));
	s.push_back(CUTE(neuralAsyncNetworkConstuctsItselfCorrectlyWithBuilderWithHiddenLayer));
	s.push_back(CUTE(neuralAsyncNetworkConstuctsItselfCorrectlyWithBuilderWithMultipleHiddenLayer));
	s.push_back(CUTE(tryConstructNeuralNetworkWithInvalidInputLayer));
	s.push_back(CUTE(tryConstructNeuralNetworkWithInvalidOutputLayer));
	s.push_back(CUTE(tryConstructNeuralNetworkWithInvalidInputLayerWithBuilder));
	s.push_back(CUTE(tryConstructNeuralNetworkWithInvalidOutputLayerWithBuilder));
	return s;
}
