#include "NeuralNetworkBuilder.h"
#include "Chessboard.h"

#include <string>
#include <cctype>
#include <iostream>

nn::NeuralNetwork createNeuralNetworkForChessboard() {
	return nn::NeuralNetworkBuilder() //
	.withInputLayerNeuronsCount(cb::Chessboard::TILES) //
	.withHiddenLayerNeuronCount(cb::Chessboard::TILES) //
	.withOutputLayerNeuronsCount(cb::Chessboard::TILES) //
	.build();
}

std::ostream& println(std::ostream &out, std::string const& s) {
	return out << s << "\n";
}

void readLocationInto(std::istream &in, std::string& s) {
	in >> s;
}

uint8_t mapLetterToNumber(char const c) {
	return std::toupper(c) - 'A';
}

cb::Position parseLocation(std::string const& s) {
	auto const x = mapLetterToNumber(*s.begin());
	uint8_t const y = *(s.begin() + 1);

	return {x, y};
}

bool validatePosition(cb::Position const& pos) {
	return pos.x < cb::Chessboard::TILES || pos.y < cb::Chessboard::TILES;
}

void placeKnightAccordingToUserInput() {
	println(std::cout, "Please place knight on chessboard");
	cb::Position position { cb::Chessboard::TILES + 1, cb::Chessboard::TILES + 1 };
	std::string s { };
	while (not validatePosition(position)) {
		readLocationInto(std::cin, s);
		position = parseLocation(s);
	}
	println(std::cout, "Placed knight on " + s);
}

void feedNeuralNetwork(cb::Chessboard const& cb, nn::NeuralNetwork& nn) {
//	auto const tiles = cb.getBoard();
//	auto& neurons = nn.getInputLayer().getNeurons();
//	for (size_t y = 0; y < cb::Chessboard::TILES; y++) {
//		for (size_t x = 0; x < cb::Chessboard::TILES; x++) {
//			auto const index = y * cb::Chessboard::TILES + x;
//			auto neuron = neurons.at(index);
//			auto const tile = tiles.at(x).at(y);
//			// TODO set the value
//		}
//	}
}

cb::Position getSuggestionFromNeuralNetwork(nn::NeuralNetwork const& nn) {
	// TODO implementation
	return {};
}

int main() {
	cb::Chessboard cb { };
	nn::NeuralNetwork nn = createNeuralNetworkForChessboard();

	// 1. let knight be placed (could also be random location)
	placeKnightAccordingToUserInput();

	// loop
	while (true) {
		// 2. Feed nn
		feedNeuralNetwork(cb, nn);
		// 3. get suggestion from nn
		auto const& pos = getSuggestionFromNeuralNetwork(nn);
		// 4. validate move
		cb.moveKnightTo(pos);

		if (not cb.isValid()) {
			// 5. if fail learn (maybe batch learning)
			// TODO implementation
		}
	}

}
