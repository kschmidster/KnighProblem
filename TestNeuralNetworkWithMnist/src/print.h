#ifndef PRINT_H_
#define PRINT_H_

#include <string>
#include <iomanip>

namespace print { /* namespace print */

template<typename T>
void println(std::ostream &ostream, T arg) {
	ostream << arg << '\n';
}

template<typename T1, typename ... T2>
void println(std::ostream &ostream, T1 arg, T2 ... args) {
	ostream << arg;
	println(ostream, args...);
}

void visualizeImage(std::ostream &ostream, char const* const image, uint32_t const rows, uint32_t const cols) {
	for (uint32_t j { }; j < rows * cols; j++) {
		if (j % rows == 0) {
			ostream << '\n';
		}
		ostream << std::setw(4) << std::to_string(static_cast<uint8_t>(image[j]));
	}
	ostream << '\n';
}

} /* end namespace print */

#endif /* PRINT_H_ */
