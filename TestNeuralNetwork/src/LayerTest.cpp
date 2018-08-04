#include "LayerTest.h"
#include "cute.h"

#include "Layer.h"
#include "Neuron.h"
#include "NeuronTest.h"
#include "TestHelper.h"

using nn::layer::Layer;
using nn::test::testLayer;

void layerDefaulConstructible() {
	ASSERT(std::is_default_constructible<Layer>::value);
}

void layerCopyConstructible() {
	ASSERT(std::is_copy_constructible<Layer>::value);
}

void layerCopyAssignable() {
	ASSERT(std::is_copy_assignable<Layer>::value);
}

void constructInputLayerWithSomeNeurons() {
	nn::InputLayer const layer { 42 };
	ASSERT_EQUAL(42, layer.getNeurons().size());
}

void constructHiddenLayerWithSomeNeurons() {
	nn::HiddenLayer const layer { 42 };
	ASSERT_EQUAL(42, layer.getNeurons().size());
}

void constructOutputLayerWithSomeNeurons() {
	nn::OutputLayer const layer { 42 };
	ASSERT_EQUAL(42, layer.getNeurons().size());
}

void connectInputWithHiddenLayerWithOneNeuronEach() {
	using namespace nn;

	InputLayer inputLayer { 1 };
	HiddenLayer hiddenLayer { 1 };

	inputLayer.connectTo(hiddenLayer);

	testLayer(inputLayer, 0, 1);
	testLayer(hiddenLayer, 1, 0);
}

void connectInputWithHiddenLayerWithNineNeuronEach() {
	using namespace nn;
	InputLayer inputLayer { 9 };
	HiddenLayer hiddenLayer { 9 };

	inputLayer.connectTo(hiddenLayer);

	testLayer(inputLayer, 0, 9);
	testLayer(hiddenLayer, 9, 0);
}

void connectInputWithHiddenLayerWithDifferenNeuronCount() {
	using namespace nn;
	InputLayer inputLayer { 9 };
	HiddenLayer hiddenLayer { 9 };

	inputLayer.connectTo(hiddenLayer);

	testLayer(inputLayer, 0, 9);
	testLayer(hiddenLayer, 9, 0);
}

void connectHiddenLayersWithOneNeuronEach() {
	using namespace nn;
	HiddenLayer hiddenLayer1 { 1 };
	HiddenLayer hiddenLayer2 { 1 };

	hiddenLayer1.connectTo(hiddenLayer2);

	testLayer(hiddenLayer1, 0, 1);
	testLayer(hiddenLayer2, 1, 0);
}

void connectHiddenLayersWithNineNeuronEach() {
	using namespace nn;
	HiddenLayer hiddenLayer1 { 9 };
	HiddenLayer hiddenLayer2 { 9 };

	hiddenLayer1.connectTo(hiddenLayer2);

	testLayer(hiddenLayer1, 0, 9);
	testLayer(hiddenLayer2, 9, 0);
}

void connectHiddenLayersWithDifferentNeuronCount() {
	using namespace nn;
	HiddenLayer hiddenLayer1 { 3 };
	HiddenLayer hiddenLayer2 { 4 };

	hiddenLayer1.connectTo(hiddenLayer2);

	testLayer(hiddenLayer1, 0, 4);
	testLayer(hiddenLayer2, 3, 0);
}

void connectHiddenLayersWithOutputLayerWithOneNeuronEach() {
	using namespace nn;
	HiddenLayer hiddenLayer { 1 };
	OutputLayer outputLayer { 1 };

	hiddenLayer.connectTo(outputLayer);

	testLayer(hiddenLayer, 0, 1);
	testLayer(outputLayer, 1, 0);
}

void connectHiddenLayersWithOutputLayerWithNineNeuronEach() {
	using namespace nn;
	HiddenLayer hiddenLayer { 9 };
	OutputLayer outputLayer { 9 };

	hiddenLayer.connectTo(outputLayer);

	testLayer(hiddenLayer, 0, 9);
	testLayer(outputLayer, 9, 0);
}

void connectHiddenLayersWithOutputLayerWithDifferenNeuronCount() {
	using namespace nn;
	HiddenLayer hiddenLayer { 3 };
	OutputLayer outputLayer { 5 };

	hiddenLayer.connectTo(outputLayer);

	testLayer(hiddenLayer, 0, 5);
	testLayer(outputLayer, 3, 0);
}

cute::suite make_suite_LayerTest() {
	cute::suite s { };
	s.push_back(CUTE(layerDefaulConstructible));
	s.push_back(CUTE(layerCopyConstructible));
	s.push_back(CUTE(layerCopyAssignable));
	s.push_back(CUTE(constructInputLayerWithSomeNeurons));
	s.push_back(CUTE(constructHiddenLayerWithSomeNeurons));
	s.push_back(CUTE(constructOutputLayerWithSomeNeurons));
	s.push_back(CUTE(connectInputWithHiddenLayerWithOneNeuronEach));
	s.push_back(CUTE(connectInputWithHiddenLayerWithNineNeuronEach));
	s.push_back(CUTE(connectInputWithHiddenLayerWithDifferenNeuronCount));
	s.push_back(CUTE(connectHiddenLayersWithOneNeuronEach));
	s.push_back(CUTE(connectHiddenLayersWithNineNeuronEach));
	s.push_back(CUTE(connectHiddenLayersWithDifferentNeuronCount));
	s.push_back(CUTE(connectHiddenLayersWithOutputLayerWithOneNeuronEach));
	s.push_back(CUTE(connectHiddenLayersWithOutputLayerWithNineNeuronEach));
	s.push_back(CUTE(connectHiddenLayersWithOutputLayerWithDifferenNeuronCount));
	return s;
}
