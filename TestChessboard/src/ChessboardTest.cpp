#include "ChessboardTest.h"
#include "cute.h"

#include "Chessboard.h"
#include "Position.h"

#include <algorithm>

void allTilesShouldBeFree() {
	cb::Chessboard const chessboard { };
	auto board = chessboard.getBoard();

	std::for_each(board.begin(), board.end(), [](auto const& line) {
		std::for_each(line.begin(), line.end(), [](cb::TileState const state) {
					ASSERT(cb::TileState::FREE == state);
				});
	});
}

void placeKnightAndCheckTileState() {
	cb::Chessboard chessboard { };
	chessboard.placeKnight(4, 4);
	ASSERT(cb::TileState::CURRENT == chessboard.getTileState(chessboard.getKnight().getPosition()));
}

void placeKnightAndMoveItCheckTiles() {
	cb::Chessboard chessboard { };
	cb::Position const start { 4, 4 };

	chessboard.placeKnight(start);
	chessboard.moveKnightTo(2, 3);

	ASSERT(cb::TileState::CURRENT == chessboard.getTileState(chessboard.getKnight().getPosition()));
	ASSERT(cb::TileState::VISITED == chessboard.getTileState(start));
}

void moveKnightAroundAndCheckTiles() {
	cb::Chessboard chessboard { };
	cb::Position const start { 4, 4 };
	cb::Position const pos1 { 2, 3 };
	cb::Position const pos2 { 3, 5 };
	cb::Position const pos3 { 4, 3 };

	chessboard.placeKnight(start);
	chessboard.moveKnightTo(pos1);
	chessboard.moveKnightTo(pos2);
	chessboard.moveKnightTo(pos3);

	ASSERT(cb::TileState::CURRENT == chessboard.getTileState(chessboard.getKnight().getPosition()));
	ASSERT(cb::TileState::VISITED == chessboard.getTileState(start));
	ASSERT(cb::TileState::VISITED == chessboard.getTileState(pos1));
	ASSERT(cb::TileState::VISITED == chessboard.getTileState(pos2));
}

void testStateAfterInvalidMove() {
	cb::Chessboard chessboard { };
	cb::Position const start { 4, 4 };

	chessboard.placeKnight(start);
	chessboard.moveKnightTo( { } );

	ASSERT(chessboard.getKnight().getPosition() == start);
	ASSERT(not chessboard.isValid());
	ASSERT(cb::TileState::CURRENT == chessboard.getTileState(chessboard.getKnight().getPosition()));
	ASSERT(cb::TileState::FREE == chessboard.getTileState( { } ));
}

cute::suite make_suite_ChessboardTest() {
	cute::suite s { };
	s.push_back(CUTE(allTilesShouldBeFree));
	s.push_back(CUTE(placeKnightAndCheckTileState));
	s.push_back(CUTE(placeKnightAndMoveItCheckTiles));
	s.push_back(CUTE(moveKnightAroundAndCheckTiles));
	s.push_back(CUTE(testStateAfterInvalidMove));
	return s;
}
