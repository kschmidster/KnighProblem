#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <utility>
#include <stdexcept>

namespace nn { /* namespace neural network */

namespace connection { /* namespace connection */

template<typename T>
std::pair<T, T> createConnection(std::initializer_list<T> list) {
	if (list.size() != 2) {
		throw std::invalid_argument { "Connection needs two arguments!" };
	}
	// TODO real ugly, there has to be another way to do this
	return std::make_pair(*list.begin(), *(list.begin() + 1));
}

} /* end namespace connection */

// template to break dependencies
template<typename T>
struct Connection {
	Connection() = default;
	explicit Connection(std::initializer_list<T> list) :
			neurons { connection::createConnection(list) } {
	}
private:
	std::pair<T, T> neurons { };
};

} /* end namespace neural network */

#endif /* CONNECTION_H_ */
