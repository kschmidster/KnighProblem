#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "NeuralNetwork.h"

void thisIsATest() {
	nn::NeuralNetwork const nn { };
	ASSERTM("start writing tests", true);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };

	//TODO add your test here
	s.push_back(CUTE(thisIsATest));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto const runner = cute::makeRunner(lis, argc, argv);
	return runner(s, "AllTests");
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
