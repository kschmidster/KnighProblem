#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <utility>

namespace nn { /* namespace neural network */

// template to break dependencies
template<typename T>
struct Connection {
	Connection() = default;
	Connection(T const& left, T const& right) :
			neurons { std::make_pair(left, right) } {
	}
private:
	std::pair<T, T> neurons { };
};

} /* end namespace neural network */

#endif /* CONNECTION_H_ */
