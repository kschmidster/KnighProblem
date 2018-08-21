#ifndef POSITION_H_
#define POSITION_H_

#include <cstdint>

namespace cb { /* namespace chessboard */

struct Position {
	Position() = default;
	Position(uint8_t x, uint8_t y) :
			x { x }, y { y } {
	}

	bool operator==(Position const& other) const {
		return x == other.x && y == other.y;
	}

	uint8_t x { };
	uint8_t y { };
};

} /* namespace chessboard */

#endif /* POSITION_H_ */
