#ifndef NEURON_H_
#define NEURON_H_

#include "Connection.h"

#include <vector>
#include <memory>

namespace nn { /* namespace neural network */

namespace neuron { /* namespace neuron */

template<typename T>
struct Neuron {
	using connection = Connection<T>;
	using connections = std::vector<connection>;
	using const_connections = std::vector<connection> const&;

	Neuron() = default;
	// Make sure this neuron is not copyable
	Neuron(Neuron const& other) = delete;
	Neuron& operator=(Neuron const& other) = delete;

	void connectTo(T& self, T& other) {
		outConnections.push_back(connection { self, other });
		other.connectFrom(self);
	}
	void connectFrom(T& from, T& self) {
		inConnections.push_back(connection { from, self });
	}

	const_connections getInConnections() const {
		return inConnections;
	}
	const_connections getOutConnections() const {
		return outConnections;
	}

private:
	connections inConnections { };
	connections outConnections { };
};

} /* end namespace neuron */

/*
 *  "Smart-Pointer" to neuron::Neuron. If we store the neuron::Neuron in the
 *  Connection we are in trouble because we copy the Neurons into the Connection.
 *  This would have a major impact.
 */
struct Neuron {
	using const_connections = std::vector<Connection<Neuron>> const&;
	using neuron = neuron::Neuron<Neuron>;
	using reference = std::shared_ptr<neuron>;

	Neuron() :
			ptr { std::make_shared<neuron>() } {
	}

	void connectTo(Neuron& other) {
		ptr.get()->connectTo(*this, other);
	}
	void connectFrom(Neuron& other) {
		ptr.get()->connectFrom(other, *this);
	}

	const_connections getInConnections() const {
		return ptr.get()->getInConnections();
	}
	const_connections getOutConnections() const {
		return ptr.get()->getOutConnections();
	}

private:
	reference ptr { };
};

} /* end namespace neural network */

#endif /* NEURON_H_ */
