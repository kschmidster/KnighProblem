#include "ConnectionTest.h"
#include "cute.h"

#include "Connection.h"

#include <type_traits>

void connectionDefaultConstructible() {
	using namespace nn;
	ASSERT(std::is_default_constructible<Connection<size_t>>::value);
}

void connectionCopyConstructible() {
	ASSERT(std::is_copy_constructible<nn::Connection<size_t>>::value);
}

void connectionCopyAssignable() {
	ASSERT(std::is_copy_assignable<nn::Connection<size_t>>::value);
}

void connectionConstructableWithNeurons() {
	size_t const & ref { 12 };

	nn::Connection<size_t>(ref, ref);
	ASSERT(true); // Everything okay if we are here
}

cute::suite make_suite_ConnectionTest() {
	cute::suite s { };
	s.push_back(CUTE(connectionDefaultConstructible));
	s.push_back(CUTE(connectionCopyConstructible));
	s.push_back(CUTE(connectionCopyAssignable));
	s.push_back(CUTE(connectionConstructableWithNeurons));
	return s;
}
