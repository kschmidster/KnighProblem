#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <utility>
#include <stdexcept>

namespace nn { /* namespace neural network */

// template to break dependencies
template<typename T>
struct Connection {
	Connection() = default;
	explicit Connection(std::initializer_list<T> list) :
			neurons { } {
		if (list.size() != 2) {
			// TODO add better message
			throw std::invalid_argument { "" };
		}
		// TODO real ugly, there has to be another way to do this
		neurons.first = *list.begin();
		neurons.second = *(list.begin() + 1);
	}
private:
	std::pair<T, T> neurons { };
};

} /* end namespace neural network */

#endif /* CONNECTION_H_ */
