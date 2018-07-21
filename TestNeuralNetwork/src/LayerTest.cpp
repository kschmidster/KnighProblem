#include "LayerTest.h"
#include "cute.h"

#include "Layer.h"

void inputLayerDefaultConstructible() {
	ASSERT(std::is_default_constructible<nn::InputLayer>::value);
}

void outputLayerDefaultConstructible() {
	ASSERT(std::is_default_constructible<nn::OutputLayer>::value);
}

void hiddenLayerDefaultConstructible() {
	ASSERT(std::is_default_constructible<nn::HiddenLayer<>>::value);
}

cute::suite make_suite_LayerTest() {
	cute::suite s { };
	s.push_back(CUTE(inputLayerDefaultConstructible));
	s.push_back(CUTE(outputLayerDefaultConstructible));
	s.push_back(CUTE(hiddenLayerDefaultConstructible));
	return s;
}
