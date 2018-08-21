#include "ValidatorTest.h"
#include "cute.h"

#include "Validator.h"
#include "Position.h"

#include <vector>
#include <algorithm>

using cb::validator::validateKnightMove;

namespace cb
::test { /* namespace cb::test */

	void fillVectorWithChessboardPositions(std::vector<cb::Position>& pos) {
		for (uint8_t i = 0; i < 64; i++) {
			for (uint8_t j = 0; j < 64; j++) {
				pos.push_back(cb::Position {i, j});
			}
		}
	}

	void removePositions(std::vector<cb::Position>& pos, std::vector<cb::Position> const& posToRemove) {
		std::remove_if(pos.begin(), pos.end(), [&posToRemove](cb::Position const p) {
					for(const auto s : posToRemove) {
						if(p == s) {
							return true;
						}
					}
					return false;
				});
	}

}
/* end namespace cb::test */

void moveToGoodPositions() {
	cb::Position const knightPos { 10, 10 };

	std::vector<cb::Position> const positions = { { 8, 9 }, { 8, 11 }, { 9, 8 }, { 9, 12 }, { 11, 8 }, { 11, 12 }, { 12, 9 }, { 12, 11 } };

	std::for_each(positions.begin(), positions.end(), [&](cb::Position const after) {
		ASSERT(validateKnightMove(knightPos, after));
	});
}

void moveToSamePosition() {
	cb::Position const knightPos { 10, 10 };
	ASSERT(not validateKnightMove(knightPos, knightPos));
}

void moveToInvalidPositions() {
	cb::Position const knightPos { 10, 10 };

	std::vector<cb::Position> const skip_positions = { { 8, 9 }, { 8, 11 }, { 9, 8 }, { 9, 12 }, { 11, 8 }, { 11, 12 }, knightPos, { 12, 9 },
			{ 12, 11 } };

	std::vector<cb::Position> visitPos { };
	cb::test::fillVectorWithChessboardPositions(visitPos);
	cb::test::removePositions(visitPos, skip_positions);

	std::for_each(visitPos.begin(), visitPos.end(), [&knightPos](cb::Position const pos) {
		ASSERT(not validateKnightMove(knightPos, pos));
	});
}

cute::suite make_suite_ValidatorTest() {
	cute::suite s { };
	s.push_back(CUTE(moveToGoodPositions));
	s.push_back(CUTE(moveToSamePosition));
	s.push_back(CUTE(moveToInvalidPositions));
	return s;
}
