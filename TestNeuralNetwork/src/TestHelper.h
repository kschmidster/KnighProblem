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

namespace tlc { /* namespace test layer connection */

struct TestLayerConnections {
	void operator()(nn::Layer const& layer,  size_t const connections) const {
		std::for_each(layer.getNeurons().begin(), layer.getNeurons().end(), [&](nn::Neuron const& neuron) {
			ASSERT_EQUAL(connections, neuron.getOutConnections().size());
		});
	}
};

} /* end namespace test layer connection */

const auto testLayer = std::bind(tlc::TestLayerConnections { }, _1, _2);

namespace tnnc { /* namespace test neural network test */

struct TestNeuralNetworkConnections {
	void operator()(nn::NeuralNetwork const& nn) const {
		using namespace nn;

		InputLayer const inputLayer = nn.getInputLayer();
		std::vector<HiddenLayer> const hiddenLayers = nn.getHiddenLayers();
		OutputLayer const outputLayer = nn.getOutputLayer();

		if (hiddenLayers.empty()) {
			testSimpleAsync(nn);
		} else {
			testLayer(inputLayer, hiddenLayers.at(0).getNeurons().size());

			if (hiddenLayers.size() == 1) {
				testLayer(hiddenLayers.at(0), outputLayer.getNeurons().size());
			} else {
				testSimpleAsyncHiddenLayer(nn);
			}

			testLayer(outputLayer, 0);
		}
	}

private:
	void testSimpleAsync(nn::NeuralNetwork const& nn) const {
		testLayer(nn.getInputLayer(), nn.getOutputLayer().getNeurons().size());
		testLayer(nn.getOutputLayer(), 0);
	}

	size_t neuronsAt(std::vector<nn::HiddenLayer> const& layers, size_t const index) const {
		return layers.at(index).getNeurons().size();
	}

	void testSimpleAsyncHiddenLayer(nn::NeuralNetwork const& nn) const {
		if (nn.getHiddenLayers().size() == 1) {
			testLayer(nn.getHiddenLayers().at(0), nn.getOutputLayer().getNeurons().size());
		} else {
			testLayer(nn.getHiddenLayers().at(0),neuronsAt(nn.getHiddenLayers(), 1));
			for (auto i = nn.getHiddenLayers().begin() + 1; i < nn.getHiddenLayers().end() - 1; i++) {
				// TODO yep, that is ugly.. do not look at it
				testLayer(*i, (*(i + 1)).getNeurons().size());
			}
			testLayer(nn.getHiddenLayers().at(nn.getHiddenLayers().size() - 1), nn.getOutputLayer().getNeurons().size());
		}
	}
};

} /* end namespace test neural network test */

const auto testNeuronalNetwork = tnnc::TestNeuralNetworkConnections { };

} /* namespace test */

#endif /* SRC_TESTHELPER_H_ */
