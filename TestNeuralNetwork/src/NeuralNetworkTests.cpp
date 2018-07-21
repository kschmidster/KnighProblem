#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "NeuralNetworkTest.h"
#include "LayerTest.h"
#include "NeuronTest.h"
#include "ConnectionTest.h"

bool runAllTestSuites(int argc, char const *argv[]) {
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);

	cute::suite s { };
	s += make_suite_NeuronTest();
	s += make_suite_ConnectionTest();
	s += make_suite_LayerTest();
	s += make_suite_NeuralNetworkTest();

	bool success = runner(s, "AllSuites");
	return success;
}

int main(int argc, char const *argv[]) {
	return runAllTestSuites(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
