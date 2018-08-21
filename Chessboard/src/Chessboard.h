#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include "Knight.h"
#include "Position.h"

#include <array>

namespace cb { /* namespace chessboard */

enum TileState
	: uint8_t {
		FREE, VISITED, CURRENT
};

struct Chessboard {
	static const size_t TILES { 64 };
	using type = std::array<std::array<TileState, TILES>, TILES>;
	using creference_chessboard = type const&;

	void placeKnight(Position const& pos) {
		placeKnight(pos.x, pos.y);
	}
	void placeKnight(uint8_t const x, uint8_t const y) {
		knight.moveTo(x, y);
		setState(knight.getPosition(), TileState::CURRENT);
	}
	void moveKnightTo(Position const& pos) {
		moveKnightTo(pos.x, pos.y);
	}
	void moveKnightTo(uint8_t const x, uint8_t const y) {
		Position const after { x, y };
		if (validateMoveTo(after)) {
			setState(knight.getPosition(), TileState::VISITED);
			knight.moveTo(after);
			setState(after, TileState::CURRENT);
		}
	}

	bool isValid() const {
		return valid;
	}
	Knight getKnight() {
		return knight;
	}
	TileState getTileState(Position const& pos) const {
		return chessboard.at(pos.x).at(pos.y);
	}
	creference_chessboard getBoard() const {
		return chessboard;
	}

private:
	TileState setState(Position const& pos, TileState const state) {
		chessboard.at(pos.x).at(pos.y) = state;
		return state;
	}
	bool validateMoveTo(Position const& after) {
		valid = knight.validateMove(after);
		return valid;
	}

	Knight knight { };
	type chessboard { };
	bool valid { true };
};

} /* end namespace chessboard */

#endif /* CHESSBOARD_H_ */
