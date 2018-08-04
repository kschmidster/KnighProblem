#ifndef SRC_TESTHELPER_H_
#define SRC_TESTHELPER_H_

#include "NeuralNetwork.h"
#include "Layer.h"

#include <vector>
#include <algorithm>
#include <functional>

namespace nn::test { /* namespace test */

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

struct testLayerConnections {
	void operator()(nn::Layer const& layer, size_t const inConnections, size_t const outConnections) const {
		std::for_each(layer.getNeurons().begin(), layer.getNeurons().end(), [&](nn::Neuron const& neuron) {
					ASSERT_EQUAL(inConnections, neuron.getInConnections().size());
					ASSERT_EQUAL(outConnections, neuron.getOutConnections().size());
				});
	}
};

const auto testLayer = std::bind(testLayerConnections { }, _1, _2, _3);

struct testNeuralNetworkConnections {
	void operator()(nn::NeuralNetwork const& nn) const {
		using namespace nn;

		InputLayer const inputLayer = nn.getInputLayer();
		std::vector<HiddenLayer> const hiddenLayers = nn.getHiddenLayers();
		OutputLayer const outputLayer = nn.getOutputLayer();

		if (hiddenLayers.empty()) {
			testSimpleAsync(nn);
		} else {
			testLayer(inputLayer, 0, hiddenLayers.at(0).getNeurons().size());

			if (hiddenLayers.size() == 1) {
				testLayer(hiddenLayers.at(0), inputLayer.getNeurons().size(), outputLayer.getNeurons().size());
			} else {
				testSimpleAsyncHiddenLayer(nn);
			}

			testLayer(outputLayer, neuronsAt(hiddenLayers, hiddenLayers.size() - 1), 0);
		}
	}

	void testSimpleAsync(nn::NeuralNetwork const& nn) const {
		testLayer(nn.getInputLayer(), 0, nn.getOutputLayer().getNeurons().size());
		testLayer(nn.getOutputLayer(), nn.getInputLayer().getNeurons().size(), 0);
	}

	size_t neuronsAt(std::vector<nn::HiddenLayer> const& layers, size_t const index) const {
		return layers.at(index).getNeurons().size();
	}

	void testSimpleAsyncHiddenLayer(nn::NeuralNetwork const& nn) const {
		if (nn.getHiddenLayers().size() == 1) {
			testLayer(nn.getHiddenLayers().at(0), nn.getInputLayer().getNeurons().size(), nn.getOutputLayer().getNeurons().size());
		} else {
			testLayer(nn.getHiddenLayers().at(0), nn.getInputLayer().getNeurons().size(), neuronsAt(nn.getHiddenLayers(), 1));
			for (auto i = nn.getHiddenLayers().begin() + 1; i < nn.getHiddenLayers().end() - 1; i++) {
				// TODO yep, that is ugly.. do not look at it
				testLayer(*i, (*(i - 1)).getNeurons().size(), (*(i + 1)).getNeurons().size());
			}
			testLayer(nn.getHiddenLayers().at(nn.getHiddenLayers().size() - 1), neuronsAt(nn.getHiddenLayers(), nn.getHiddenLayers().size() - 2),
					nn.getOutputLayer().getNeurons().size());
		}
	}
};

const auto testNeuronalNetwork = testNeuralNetworkConnections { };

} /* namespace test */

#endif /* SRC_TESTHELPER_H_ */
