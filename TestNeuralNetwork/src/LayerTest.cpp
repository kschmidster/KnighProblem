#include "LayerTest.h"
#include "cute.h"

#include "Layer.h"

using nn::layer::Layer;

void layerDefaulConstructible() {
	ASSERT(std::is_default_constructible<Layer>::value);
}

void layerCopyConstructible() {
	ASSERT(std::is_copy_constructible<Layer>::value);
}

void layerCopyAssignable() {
	ASSERT(std::is_copy_assignable<Layer>::value);
}

void hiddenLayerDefaultConstructible() {
	ASSERT(std::is_default_constructible<nn::HiddenLayer>::value);
}

void hiddenLayerCopyConstructible() {
	ASSERT(std::is_copy_constructible<nn::HiddenLayer>::value);
}

void hiddenLayerCopyAssignable() {
	ASSERT(std::is_copy_assignable<nn::HiddenLayer>::value);
}

void constructInputLayerWithSomeNeurons() {
	nn::InputLayer const layer { 42 };
	ASSERT(true); // Everything okay if we are here
}

void constructHiddenLayerWithSomeNeurons() {
	nn::HiddenLayer const layer { 42 };
	ASSERT(true); // Everything okay if we are here
}

void constructOutputLayerWithSomeNeurons() {
	nn::OutputLayer const layer { 42 };
	ASSERT(true); // Everything okay if we are here
}

cute::suite make_suite_LayerTest() {
	cute::suite s { };
	s.push_back(CUTE(layerDefaulConstructible));
	s.push_back(CUTE(layerCopyConstructible));
	s.push_back(CUTE(layerCopyAssignable));
	s.push_back(CUTE(hiddenLayerDefaultConstructible));
	s.push_back(CUTE(hiddenLayerCopyConstructible));
	s.push_back(CUTE(hiddenLayerCopyAssignable));
	s.push_back(CUTE(constructInputLayerWithSomeNeurons));
	s.push_back(CUTE(constructHiddenLayerWithSomeNeurons));
	s.push_back(CUTE(constructOutputLayerWithSomeNeurons));
	return s;
}
