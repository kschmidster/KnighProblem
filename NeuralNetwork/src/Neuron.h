#ifndef NEURON_H_
#define NEURON_H_

#include "Connection.h"

#include <cmath>
#include <vector>
#include <memory>
#include <algorithm>

namespace nn { /* namespace neural network */

namespace neuron { /* namespace neuron */

template<typename T>
struct Neuron {
	using connection = Connection<T>;
	using conns = std::vector<connection>;
	using const_connections = std::vector<connection> const&;

	Neuron() = default;
	// Make sure this neuron is not copyable
	Neuron(Neuron const& other) = delete;
	Neuron& operator=(Neuron const& other) = delete;

	void connectTo(T& other, float weight) {
		connections.push_back(connection { other, weight });
	}

	template<typename T1>
	void setInput(T1 input) {
		value = input;
	}
	template<typename T1>
	void addInput(T1 input) {
		value += input;
	}
	void clearInput() {
		value = 0.0;
	}
	void processInput() {
		sendOutput(sigmoidOf(value));
	}

	void randomizeConnections() {
		std::for_each(connections.begin(), connections.end(), [](Connection<T> &connection) {
			connection.setRandomWeight();
		});
	}

	static double sigmoidOf(double const value) {
			return 1.0 / (1.0 + std::exp(- value));
	}

	double getValue() const {
		return value;
	}
	const_connections getConnections() const {
		return connections;
	}

private:
	void sendOutput(double output) {
		std::for_each(connections.begin(), connections.end(), [&output](Connection<T> &connection) {
			double input = connection.getWeight() * output;
			connection.getNeuron().addInput(input);
		});
	}

	double value { };
	conns connections { };
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

	void connectTo(Neuron& other, float const weight = 0.f) {
		ptr.get()->connectTo(other, weight);
	}

	template<typename T>
	void setInput(T input) {
		ptr.get()->setInput(input);
	}
	template<typename T>
	void addInput(T input) {
		ptr.get()->addInput(input);
	}
	void clearInput() {
		ptr.get()->clearInput();
	}
	void processInput() {
		ptr.get()->processInput();
	}

	void randomizeWeights() {
		ptr.get()->randomizeConnections();
	}

	double getValue() const {
		return ptr.get()->getValue();
	}
	const_connections getOutConnections() const {
		return ptr.get()->getConnections();
	}

private:
	reference ptr { };
};

} /* end namespace neural network */

#endif /* NEURON_H_ */
