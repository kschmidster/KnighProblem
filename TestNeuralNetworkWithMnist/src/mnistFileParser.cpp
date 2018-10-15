#include "mnistFileParser.h"

#include "print.h"

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <iostream>
#include <stdexcept>

namespace mnist { /* namespace mnist */

const std::string LABEL_FILE_PATH { "./resources/train-labels.idx1-ubyte" };
const std::string IMAGE_FILE_PATH { "./resources/train-images.idx3-ubyte" };
constexpr uint32_t MAGIC_NUMBER_LABELS { 2049 };
constexpr uint32_t MAGIC_NUMBER_IMAGES { 2051 };
constexpr uint32_t NUMBER_OF_ENTRIES { 60000 };

uint32_t swap_endian(uint32_t val) {
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

template<typename T>
uint32_t readFromFile(std::ifstream &file) {
	T type { };
	file.read(reinterpret_cast<char*>(&type), sizeof(T));
	return type;
}

template<typename T>
uint32_t readFromFileAndSwapEndian(std::ifstream &file) {
	return swap_endian(readFromFile<T>(file));
}

void checkPreambleOfLabelFile(std::ostream &ostream, std::ifstream &labelStream) {
	uint32_t i32 = readFromFileAndSwapEndian<uint32_t>(labelStream);
	if (MAGIC_NUMBER_LABELS != i32) {
		throw std::runtime_error { "Magic number error from label file" };
	}
	print::println(ostream, "Magic number of labels: ", i32);

	i32 = readFromFileAndSwapEndian<uint32_t>(labelStream);
	if (NUMBER_OF_ENTRIES != i32) {
		throw std::runtime_error { "Number of entries error from label file" };
	}
	print::println(ostream, "Number of labels: ", i32);
}

std::pair<uint32_t, uint32_t> checkPreambleOfImageFile(std::ostream &ostream, std::ifstream &imageStream) {
	std::pair<uint32_t, uint32_t> values { };

	uint32_t i32 = readFromFileAndSwapEndian<uint32_t>(imageStream);
	if (MAGIC_NUMBER_IMAGES != i32) {
		throw std::runtime_error { "Magic number error from image file" };
	}
	print::println(ostream, "Number of images: ", i32);

	i32 = readFromFileAndSwapEndian<uint32_t>(imageStream);
	if (NUMBER_OF_ENTRIES != i32) {
		throw std::runtime_error { "Number of entries error from image file" };
	}
	print::println(ostream, "Magic number of images: ", i32);

	values.first = readFromFileAndSwapEndian<uint32_t>(imageStream);
	values.second = readFromFileAndSwapEndian<uint32_t>(imageStream);

	print::println(ostream, "images are ", values.first, 'x', values.second, " big");

	return values;
}

std::vector<char> toVector(char const* const image, uint32_t const imageSize) {
	std::vector<char> pic(imageSize);

	for (uint32_t i { }; i < imageSize; i++) {
		pic.at(i) = image[i];
	}

	return pic;
}

auto readImagesWithLabels(std::ostream& ostream, std::ifstream& labelStream, std::ifstream& imageStream,
		std::pair<uint32_t, uint32_t> const &rowsCols) {
	using pair = std::pair<int, std::vector<char>>;

	pair temp { };
	std::vector<pair> labelWithImage { NUMBER_OF_ENTRIES };
	uint32_t const imageSize = rowsCols.first * rowsCols.second;

	// TODO not quite sure if I have to use the heap
	std::unique_ptr<char[]> const ptr { new char[imageSize] { } };
	for (uint32_t i { }; i < NUMBER_OF_ENTRIES; i++) {
		// Oh boy.. all those castings...
		temp.first = static_cast<int>(readFromFile<char>(labelStream));
		print::println(ostream, "label ", i, " is the number: ", temp.first);

		imageStream.read(ptr.get(), imageSize);
//		print::visualizeImage(ostream, ptr.get(), rowsCols.first, rowsCols.second);
		print::println(ostream, "Loaded number with label: ", temp.first);
		temp.second = toVector(ptr.get(), imageSize);

		labelWithImage.at(i) = temp;
	}

	return labelWithImage;
}

auto getImagesWithLabels(std::ostream &ostream, std::ifstream &labelStream, std::ifstream &imageStream) {
	checkPreambleOfLabelFile(ostream, labelStream);
	auto const rowsCols = checkPreambleOfImageFile(ostream, imageStream);

	return readImagesWithLabels(ostream, labelStream, imageStream, rowsCols);
}

std::vector<std::pair<int, std::vector<char>>> readImagesFromFiles(std::ostream &ostream) {
	std::ifstream labelStream { LABEL_FILE_PATH, std::ios::binary };
	std::ifstream imageStream { IMAGE_FILE_PATH, std::ios::binary };
	if (!labelStream.is_open() || !imageStream.is_open()) {
		print::println(std::cerr, "Could not open file: ", LABEL_FILE_PATH, " or ", IMAGE_FILE_PATH);
	} else {
		return getImagesWithLabels(ostream, labelStream, imageStream);
	}
	return std::vector<std::pair<int, std::vector<char>>> { };
}

} /* end namespace mnist */
