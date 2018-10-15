#ifndef MNISTFILEPARSER_H_
#define MNISTFILEPARSER_H_

#include <vector>
#include <fstream>
#include <utility>

namespace mnist { /* namespace mnist */

uint32_t swap_endian(uint32_t val);

template<typename T>
uint32_t readFromFile(std::ifstream &file);

template<typename T>
uint32_t readFromFileAndSwapEndian(std::ifstream &file);

void checkPreambleOfLabelFile(std::ostream &ostream, std::ifstream &labelStream);

std::pair<uint32_t, uint32_t> checkPreambleOfImageFile(std::ostream &ostream, std::ifstream &imageStream);

std::vector<char> toVector(char const* const image, uint32_t const imageSize);

auto readImagesWithLabels(std::ostream& ostream, std::ifstream& labelStream, std::ifstream& imageStream,
		std::pair<uint32_t, uint32_t> const &rowsCols);

auto getImagesWithLabels(std::ostream &ostream, std::ifstream &labelStream, std::ifstream &imageStream);

std::vector<std::pair<int, std::vector<char>>> readImagesFromFiles(std::ostream &ostream);

} /* end namespace mnist */

#endif /* MNISTFILEPARSER_H_ */
