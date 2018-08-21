#ifndef KNIGHT_H_
#define KNIGHT_H_

#include "Position.h"
#include "Validator.h"

namespace cb { /* namespace chessboard */

struct Knight {
	void moveTo(Position const& newPos) {
		moveTo(newPos.x, newPos.y);
	}
	void moveTo(uint8_t const x, uint8_t const y) {
		position.x = x;
		position.y = y;
	}

	bool validateMove(Position const& newPos) const {
		return validator::validateKnightMove(position, newPos);
	}

	Position getPosition() const {
		return position;
	}
private:
	Position position { };
};

} /* end namespace chessboard */

#endif /* KNIGHT_H_ */
