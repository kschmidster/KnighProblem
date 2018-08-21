#include "NeuralNetworkTest.h"
#include "cute.h"

#include "NeuralNetwork.h"
#include "Layer.h"
#include "TestHelper.h"

#include <vector>
#include <utility>
#include <stdexcept>

using nn::test::testNeuronalNetwork;

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

void tryConstructNeuralNetworkWithInvalidInputLayer() {
	using namespace nn;
	ASSERT_THROWS((NeuralNetwork { InputLayer { }, OutputLayer { } }), std::invalid_argument);
}

void tryConstructNeuralNetworkWithInvalidOutputLayer() {
	using namespace nn;
	ASSERT_THROWS((NeuralNetwork { InputLayer { 1 }, OutputLayer { } }), std::invalid_argument);
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
	s.push_back(CUTE(tryConstructNeuralNetworkWithInvalidInputLayer));
	s.push_back(CUTE(tryConstructNeuralNetworkWithInvalidOutputLayer));
	return s;
}
