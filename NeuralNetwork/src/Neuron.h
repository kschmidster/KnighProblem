#ifndef NEURON_H_
#define NEURON_H_

#include "Connection.h"

#include <vector>
#include <memory>

namespace nn { /* namespace neural network */

namespace neuron { /* namespace neuron */

// template to break dependencies
template<typename T>
struct NeuronImpl {
  void connect(T const& ptr, T const& other) {
      inConnections.push_back( Connection<T>{ ptr, other } );
  }
private:
  std::vector<Connection<T>> inConnections { };
  std::vector<Connection<T>> outConnections { };
};

} /* end namespace neuron */

struct Neuron {
  Neuron() : neuron { std::make_shared<neuron::NeuronImpl<Neuron>>() } {
  }
  void connect(Neuron const& other) const {
	  neuron.get()->connect(*this, other);
  }
private:
  std::shared_ptr<neuron::NeuronImpl<Neuron>> neuron { };
};

} /* end namespace neural network */

#endif /* NEURON_H_ */
