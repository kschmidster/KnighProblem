#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <utility>

namespace nn { /* namespace neural network */

template<typename T>
struct Connection {
	Connection() = default;
	Connection(T& left, T& right, float weight = 0.f) :
			neurons { left, right }, weight { weight } {
	}
private:
	// TODO std::reference_wrapper instead of T maybe?
	std::pair<T, T> neurons { };
	float weight { };
};

} /* end namespace neural network */

#endif /* CONNECTION_H_ */
