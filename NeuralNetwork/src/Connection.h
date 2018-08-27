#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <random>

namespace nn { /* namespace neural network */

// template to break dependencies
template<typename T>
struct Connection {
	Connection() = default;
	Connection(T to, float weight = .0f) :
			to { to }, weight { weight } {
	}

	void setRandomWeight() {
		this->weight = random();
	}
	void setWeight(float weight) {
		this->weight = weight;
	}

	T getNeuron() const {
		return to;
	}

	float getWeight() const {
		return weight;
	}
private:
	T to { };
	float weight { };

	// TODO is it possible to extract this to a functor or similar
	// so that the objects dont have to be instantiated every time
	double random() const {
		std::random_device randomDevice { };
		std::mt19937 twister { randomDevice() };
		std::uniform_real_distribution<> distributor { -0.99999, 1.0 };
		return distributor(twister);
	}
};

} /* end namespace neural network */

#endif /* CONNECTION_H_ */
