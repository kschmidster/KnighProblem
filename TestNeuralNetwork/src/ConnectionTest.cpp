#include "ConnectionTest.h"
#include "cute.h"

#include "Connection.h"

#include <type_traits>

void connectionDefaultConstructible() {
	using namespace nn;
	ASSERT(std::is_default_constructible<Connection<int>>::value);
}

void connectionConstructableWithNeurons() {
	using namespace nn;
	int number { 12 };
	int& ref { number };

	Connection<int>(ref, ref);
	ASSERT(true); // Everything ok, if we are here
}

cute::suite make_suite_ConnectionTest() {
	cute::suite s { };
	s.push_back(CUTE(connectionDefaultConstructible));
	s.push_back(CUTE(connectionConstructableWithNeurons));
	return s;
}
