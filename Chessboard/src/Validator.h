#ifndef VALIDATOR_H_
#define VALIDATOR_H_

#include "Position.h"

namespace cb
::validator { /* namespace validator */

	namespace mv { /* namespace mv */

		struct KnightMoveValidator {
			bool operator()(Position const& before, Position const& after) const {
				char const xBefore = before.x;
				char const yBefore = before.y;
				char const xAfter = after.x;
				char const yAfter = after.y;

				if (positionTwoOff(xBefore, xAfter)) {
					return positionOneOff(yBefore, yAfter);
				}
				if (positionOneOff(xBefore, xAfter)) {
					return positionTwoOff(yBefore, yAfter);
				}
				return false;
			}

		private:
			bool positionOneOff(char const before, char const after) const {
				return before + 1 == after || before - 1 == after;
			}
			bool positionTwoOff(char const before, char const after) const {
				return before + 2 == after || before - 2 == after;
			}
		};

	} /* end namespace mv */

	const auto validateKnightMove = mv::KnightMoveValidator {};

}
/* end namespace validator */

#endif /* VALIDATOR_H_ */
